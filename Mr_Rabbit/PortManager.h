#ifndef PortManager_h
#define PortManager_h

#include <Arduino.h>
#include <WiFi.h>
#include "Parameters.h"

// === Port & Challenge Variables ===
uint16_t openPorts[MAX_OPEN_PORTS];  // Telnet-like open ports
uint8_t openPortsCount = 0;

uint16_t hiddenPort;              // Randomly selected hidden port
String hiddenUsername;            // Randomly generated username for hidden access
String hiddenPassword;            // Random password for hidden access
String secretWord;                // Secret string shown to authenticated user
IPAddress triggerIP;              // IP used to activate hidden port
uint16_t triggerPort;             // One of the open ports used for hidden trigger

// Parse open ports
void parseOpenPorts(const char* portsStr) {
  String str = String(portsStr);
  int index = 0;

  while (str.length() > 0 && index < MAX_OPEN_PORTS) {
    int commaIndex = str.indexOf(',');
    String portStr;

    if (commaIndex >= 0) {
      portStr = str.substring(0, commaIndex);
      str = str.substring(commaIndex + 1);
    } else {
      portStr = str;
      str = "";
    }

    portStr.trim();
    if (portStr.length() > 0) {
      openPorts[index++] = portStr.toInt();
    }
  }

  openPortsCount = index;
}

void initPorts() {
  parseOpenPorts(OPEN_PORTS_STRING);

  // Select random hidden port
  hiddenPort = random(5000, 9999);
  for (int i = 0; i < openPortsCount; i++) {
    if (hiddenPort == openPorts[i]) {
      hiddenPort = random(5000, 9999);
      i = -1; // Restart check
    }
  }

  // Generate trigger IP
  triggerIP = WiFi.localIP();
  triggerIP[3] = random(100, 200);
  while (triggerIP == WiFi.localIP()) {
    triggerIP[3] = random(100, 200);
  }

  // Generate challenge data
  hiddenUsername = "user" + String(random(1000, 9999));
  hiddenPassword = "pass" + String(random(1000, 9999));
  secretWord = "RABBIT" + String(random(10000, 99999));
  triggerPort = openPorts[random(0, openPortsCount)];
}

#endif
