#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include "BuzzerPlayer.h"
#include "EarsMove.h"
#include "Telegram.h"
#include "WiFiManager.h"
#include "PortManager.h"
#include "ServerManager.h"
#include "Sessions.h"
#include "Jump.h"


unsigned long lastJump = 0;
const unsigned long JUMP_INTERVAL = 600000; // Time after which the hidden port and credentials will change

unsigned long lastBroadcast = 0;      // Time of last UDP broadcast


void setup() {
  Serial.begin(115200);                 // Start serial communication for debugging at 115200 baud rate
  setupEars();                          // Initialize servo motors or hardware related to "ears"
  setupBuzzer();                        // Set up the buzzer (likely configure pin mode, initial state, etc.)
  connectToRandomWiFi();               // Connect to a randomly chosen Wi-Fi network from the ssids[] list
  randomSeed(micros());                // Seed the random number generator using a high-resolution timer (more randomness)
  initPorts();                         // Initialize GPIO ports and possibly configure authentication keys or ports
  startServers();                      // Launch Telnet and hidden servers for network interaction
  sendTelegramStart(startIP);          // Optional: Send a Telegram message to notify that the system has started (with its IP)
  playRabbitJump();                    // Play a startup sound or animation (e.g., a tone or melody indicating the "rabbit" is jumping)
  moveEars();                          // Perform initial ear movement for a visual effect (like wagging or scanning)
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