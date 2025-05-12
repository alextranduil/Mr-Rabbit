#ifndef PortManager_h
#define PortManager_h

#include <WiFi.h>

uint16_t openPorts[3];            // Telnet-like open ports (in this example: 23, 2323, 4242)
uint16_t hiddenPort;              // Randomly selected hidden port
String hiddenUsername;            // Randomly generated username for hidden access
String hiddenPassword;            // Random password for hidden access
String secretWord;                // Secret string shown to authenticated user
IPAddress triggerIP;              // Fake IP used to activate hidden port
uint16_t triggerPort;             // One of the open ports used for hidden trigger

void initPorts() {
  openPorts[0] = 23; // you may change these ports
  openPorts[1] = 2323;
  openPorts[2] = 4242;

  // Select random port for hidden server
  hiddenPort = random(5000, 9999);
  while (hiddenPort == openPorts[0] || hiddenPort == openPorts[1] || hiddenPort == openPorts[2]) {
    hiddenPort = random(5000, 9999);
  }

  // Generate trigger IP (used as fake bait)
  triggerIP = WiFi.localIP();
  triggerIP[3] = random(100, 200);
  while (triggerIP == WiFi.localIP()) {
    triggerIP[3] = random(100, 200);
  }

  // Generate random credentials and secret
  hiddenUsername = "user" + String(random(1000, 9999));
  hiddenPassword = "pass" + String(random(1000, 9999));
  secretWord = "RABBIT" + String(random(10000, 99999));
  triggerPort = openPorts[random(0, 3)];
}

#endif