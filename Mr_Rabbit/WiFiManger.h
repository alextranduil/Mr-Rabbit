#ifndef WiFiManager_h
#define WiFiManager_h

#include <WiFi.h>
#include <WiFiUdp.h>

#include "Secrets.h"

WiFiUDP udp;                       // UDP for broadcasting messages
IPAddress broadcastIP;            // IP address for broadcasting messages
IPAddress startIP;                // Initial IP after connecting to Wi-Fi

void connectToRandomWiFi() {
  WiFi.mode(WIFI_STA);
  int idx = random(0, sizeof(ssids) / sizeof(ssids[0]));  // Choose a random Wi-Fi network
  WiFi.begin(ssids[idx], passwords[idx]);
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry++ < 20) {
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    startIP = WiFi.localIP();
    broadcastIP = WiFi.localIP();
    broadcastIP[3] = 255;  // Set broadcast address to .255
  } else {
    ESP.restart();  // Restart if unable to connect
  }
}

void broadcastMessage() {
  // Periodically broadcast the message with tip
  String msg = "My friend, I am waiting for you from: " + triggerIP.toString();
  udp.beginPacket(broadcastIP, 5555);
  udp.print(msg);
  udp.endPacket();
}

#endif