#ifndef ServerManager_h
#define ServerManager_h

#include <WiFi.h>
#include "PortManager.h"

WiFiServer* defaultServers[3];     // Servers for open ports
WiFiServer* hiddenServer = nullptr; // Server for hidden access

void startServers() {
  for (int i = 0; i < 3; i++) {
    defaultServers[i] = new WiFiServer(openPorts[i]);
    defaultServers[i]->begin();
  }
  hiddenServer = new WiFiServer(hiddenPort);
  hiddenServer->begin();
}

#endif