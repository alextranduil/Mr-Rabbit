#ifndef Sessions_h
#define Sessions_h

#include "Secrets.h"
#include "ASCIIRabbit.h"
#include <WiFi.h>

// Telnet session structure
struct TelnetSession {
  WiFiClient client;
  bool isHidden;
  unsigned long startTime;
  bool authed = false;
  String userBuf = "";
  String passBuf = "";
  bool awaitingFullName = false;
  bool sentIntro = false;
};

TelnetSession sessions[MAX_SESSIONS]; // Array of active sessions

bool hiddenPortOpen = false;          // If hidden port is active
bool taskCompleted = false;

// check new Telnet connection
void checkNewConnections() {
  for (int i = 0; i < 3; i++) {
    WiFiClient c = defaultServers[i]->available();
    if (c) handleNewClient(c, false);
  }
  WiFiClient hc = hiddenServer->available();
  if (hc) handleNewClient(hc, true);
}

// start handling new telnet session and greetings
void handleNewClient(WiFiClient client, bool isHidden) {
  for (int i = 0; i < MAX_SESSIONS; i++) {
    if (!sessions[i].client || !sessions[i].client.connected()) {
      sessions[i] = {client, isHidden, millis()};
      // Send welcome banner with ASCII art
      client.println(" _____                                                                        _____ ");
      client.println("( ___ )                                                                      ( ___ )");
      client.println(" |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | ");
      client.println(" |   |                    _      __    __                                     |   | ");
      client.println(" |   |                   | | /| / /__ / /______  __ _  ___                    |   | ");
      client.println(" |   |                   | |/ |/ / -_) / __/ _ \\/  ' \\/ -_)                   |   | ");
      client.println(" |   |                   |__/|__/\\__/_/\\__/\\___/_/_/_/\\__/                    |   | ");
      client.println(" |   |   __         __  __          __  ___         ___       __   __   _ __  |   | ");
      client.println(" |   |  / /____    / /_/ /  ___    /  |/  /___     / _ \\___ _/ /  / /  (_) /_ |   | ");
      client.println(" |   | / __/ _ \\  / __/ _ \\/ -_)  / /|_/ / __/    / , _/ _ `/ _ \\/ _ \\/ / __/ |   | ");
      client.println(" |   | \\__/\\___/  \\__/_//_/\\__/  /_/  /_/_/ (_)  /_/|_|\\_,_/_.__/_.__/_/\\__/  |   | ");
      client.println(" |   |               _______        ____                     __               |   | ");
      client.println(" |   |              / ___/ /  ___ _/ / /__ ___  ___ ____    / /               |   | ");
      client.println(" |   |             / /__/ _ \\/ _ `/ / / -_) _ \\/ _ `/ -_)  /_/                |   | ");
      client.println(" |   |             \\___/_//_/\\_,_/_/_/\\__/_//_/\\_, /\\__/  (_)                 |   | ");
      client.println(" |   |                                          /_/                           |   | ");
      client.println(" |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| ");
      client.println("(_____)                                                                      (_____)");
      return;
    }
  }
  client.println("Too many connections, try later.");
  client.stop();
}

// handle of the telnet session
void handleSessions() {
  for (int i = 0; i < MAX_SESSIONS; i++) {
    TelnetSession& s = sessions[i];
    if (!s.client || !s.client.connected()) continue;

    unsigned long timeout = s.isHidden ? HIDDEN_TIMEOUT : TELNET_TIMEOUT;

    if (s.isHidden && !hiddenPortOpen) {
      s.client.println("Access denied.");
      s.client.flush();
      s.client.stop();
      continue;
    }

    if (millis() - s.startTime > timeout) {
      s.client.println("Session timeout.");
      s.client.flush();
      s.client.stop();
      continue;
    }

    // Show intro art ONCE upon connection
    if (!s.authed && !s.sentIntro) {
      s.sentIntro = true;
      s.client.println("Please enter your rabbitname:");
      delay(5000);
      return;
    }

    while (s.client.available()) {
      String input = s.client.readStringUntil('\n');
      input.trim();

      if (!s.authed) {
        // === Trigger port logic (rabbit + carrot) ===
        if (s.client.remoteIP() == triggerIP && s.client.localPort() == triggerPort) {
          if (s.userBuf.isEmpty()) {
            s.userBuf = input;
            s.client.println("Rabbitname accepted.");
            s.client.println("Now enter passcarrot:");
            delay(5000);
            return;
          }

          if (s.passBuf.isEmpty()) {
            s.passBuf = input;
            if (s.userBuf == "rabbit" && s.passBuf == "carrot") {
              s.authed = true;
              hiddenPortOpen = true;
              showRabbit(s.client);
              s.client.flush();
              delay(3000);
              s.client.stop();
            } else {
              s.client.println("Incorrect. Your rabbitname isn't 'rabbit' and your passcarrot isn't 'carrot'.");
              s.client.flush();
              delay(2000);
              s.client.stop();
            }
            return;
          }
        }

        // === Hidden port authentication ===
        else if (s.isHidden) {
          if (s.userBuf.isEmpty()) {
            s.userBuf = input;
            s.client.println("Rabbitname accepted.");
            s.client.println("Now enter passcarrot:");
            delay(5000);
            return;
          }

          if (s.passBuf.isEmpty()) {
            s.passBuf = input;
            if (s.userBuf == hiddenUsername && s.passBuf == hiddenPassword) {
              s.authed = true;
              s.client.println("Please enter your full name on English: ");
              delay(20000);
              s.awaitingFullName = true;
            } else {
              s.client.println("Wrong rabbitname and/or passcarrot!");
              s.client.flush();
              delay(2000);
              s.client.stop();
            }
            return;
          }
        }

        // === Default wrong port ===
        else {
          sendFakeRabbit(s.client, s.client.localPort() == triggerPort);
          s.client.flush();
          delay(2000);
          s.client.stop();
          return;
        }
      }

      // === Handle full name ===
      else if (s.awaitingFullName) {
        s.awaitingFullName = false;
        String fullName = input;
        showFinalRabbit(s.client, fullName, secretWord);
        sendTelegramMessage(s.client.remoteIP(), hiddenPort, hiddenUsername, hiddenPassword, fullName, secretWord);
        playExtendedZeldaFanfare();
        moveEars();
        s.client.flush();
        delay(4000);
        s.client.stop();
        jump();
      }
    }
  }
}

#endif