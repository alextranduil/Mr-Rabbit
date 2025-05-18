#ifndef ServerManager_h
#define ServerManager_h

#include "PortManager.h"

WiFiServer* defaultServers[MAX_OPEN_PORTS];     // Servers for open ports
WiFiServer* hiddenServer = nullptr; // Server for hidden access

// Start servers
void startServers() {
  for (int i = 0; i < MAX_OPEN_PORTS; i++) {
    defaultServers[i] = new WiFiServer(openPorts[i]);
    defaultServers[i]->begin();
  }
  hiddenServer = new WiFiServer(hiddenPort);
  hiddenServer->begin();
}

#endif