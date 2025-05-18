#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include "Parameters.h"
#include "BuzzerPlayer.h"
#include "EarsMove.h"
#include "Telegram.h"
#include "WiFiManager.h"
#include "ServerManager.h"
#include "Sessions.h"

unsigned long lastJump = 0;           // Time of last jump
unsigned long lastBroadcast = 0;      // Time of last UDP broadcast

void setup() {
  Serial.begin(115200);                 // Start serial communication for debugging at 115200 baud rate
  setupEars();                          // Initialize servo motors related to "ears"
  setupBuzzer();                        // Set up the buzzer
  connectToRandomWiFi();               // Connect to a randomly chosen Wi-Fi network from the ssids[] list
  randomSeed(micros());                // Seed the random number generator using a high-resolution timer
  initPorts();                         // Configure authentication keys and ports
  startServers();                      // Launch Telnet and hidden servers for network interaction
  sendTelegramStart(startIP);          // Send a Telegram message to notify that the system has started (with its IP)
  playRabbitJump();                    // Play a melody indicating the "rabbit" is jumping
  moveEars();                          // Perform initial ear movement for a visual effect 
}

void loop() {
  if (millis() - lastBroadcast > BROADCAST_INTERVAL) {
    lastBroadcast = millis();
    broadcastMessage();
  }
  checkNewConnections();  // Accept new client connections
  handleSessions();       // Manage all existing sessions
  if (millis() - lastJump > JUMP_INTERVAL) {
    jump();               // Regenerate all values
  }
}