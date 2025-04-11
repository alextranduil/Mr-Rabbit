#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>

#define LED_PIN 2                      // GPIO pin connected to the onboard LED
#define MAX_SESSIONS 5                // Maximum number of concurrent telnet sessions
#define BROADCAST_INTERVAL 3000       // Interval for broadcasting message (in ms)
#define TELNET_TIMEOUT 30000          // Timeout for regular telnet sessions (in ms)
#define HIDDEN_TIMEOUT 60000          // Timeout for hidden port sessions (in ms)

const char* ssids[] = {""};           // List of possible Wi-Fi SSIDs (fill in)
const char* passwords[] = {""};       // Corresponding Wi-Fi passwords (fill in)

const String BOT_TOKEN = "";          // Telegram bot token (fill in)
const String CHAT_ID   = "";          // Telegram chat ID to send messages to (fill in)

WiFiUDP udp;                          // UDP object for broadcasting messages
IPAddress broadcastIP;               // IP address for broadcast

WiFiServer* defaultServers[3];       // Array of 3 WiFiServer objects for standard ports
WiFiServer* hiddenServer = nullptr;  // Pointer to WiFiServer for hidden port

uint16_t openPorts[3];               // List of 3 open (default) ports
uint16_t hiddenPort;                 // Random hidden port

String hiddenUsername;               // Username for accessing hidden port
String hiddenPassword;               // Password for accessing hidden port
String secretWord;                   // Secret word shown upon successful connection
IPAddress triggerIP;                 // Specific IP required to trigger hidden port
uint16_t triggerPort;                // Specific open port used to trigger hidden port

// Structure representing a Telnet session
struct TelnetSession {
  WiFiClient client;                 // TCP client object
  bool isHidden;                     // Whether this session is via hidden port
  unsigned long startTime;          // Timestamp when session started
  bool authed = false;              // Whether authentication is successful
  String userBuf = "";              // Buffer for entered username
  String passBuf = "";              // Buffer for entered password
  bool awaitingFullName = false;    // Whether waiting for user to enter full name
};

TelnetSession sessions[MAX_SESSIONS]; // Array of concurrent sessions

unsigned long lastBroadcast = 0;      // Timestamp of last broadcast
bool hiddenPortOpen = false;          // Flag if hidden port access is enabled
bool taskCompleted = false;           // Flag if task was completed (used later if needed)

void setup() {
  Serial.begin(115200);               // Start serial communication
  pinMode(LED_PIN, OUTPUT);          // Set LED pin as output
  connectToRandomWiFi();             // Connect to a random Wi-Fi from the list
  randomSeed(micros());              // Initialize random seed
  initPorts();                       // Initialize open and hidden ports
  startServers();                    // Start WiFi servers on all ports
}

void connectToRandomWiFi() {
  WiFi.mode(WIFI_STA);               // Set WiFi mode to Station
  int idx = random(3);               // Pick a random SSID
  Serial.println("[WIFI] Connecting to: " + String(ssids[idx]));
  WiFi.begin(ssids[idx], passwords[idx]);
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry++ < 20) {
    delay(500);                      // Wait while attempting to connect
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WIFI] Connected: " + WiFi.localIP().toString());
    broadcastIP = WiFi.localIP();    // Set broadcast IP
    broadcastIP[3] = 255;            // Modify last octet for broadcast
  } else {
    Serial.println("[WIFI] Failed to connect.");
    ESP.restart();                   // Restart device if connection fails
  }
}

void initPorts() {
  openPorts[0] = 23;                 // Default telnet ports
  openPorts[1] = 2323;
  openPorts[2] = 4242;

  // Generate a unique hidden port different from openPorts
  hiddenPort = random(3000, 9999);
  while (hiddenPort == openPorts[0] || hiddenPort == openPorts[1] || hiddenPort == openPorts[2]) {
    hiddenPort = random(3000, 9999);
  }

  // Generate a trigger IP different from local IP
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

  // Debug output
  Serial.println("[PORTS] Open ports: " + String(openPorts[0]) + ", " + String(openPorts[1]) + ", " + String(openPorts[2]));
  Serial.println("[HIDDEN] Port: " + String(hiddenPort));
  Serial.println("[TRIGGER] Port: " + String(triggerPort));
  Serial.println("[TRIGGER IP] " + triggerIP.toString());
}

void startServers() {
  // Start telnet servers on the open ports
  for (int i = 0; i < 3; i++) {
    defaultServers[i] = new WiFiServer(openPorts[i]);
    defaultServers[i]->begin();
    Serial.println("[SERVER] Listening on port " + String(openPorts[i]));
  }
  // Start server on hidden port
  hiddenServer = new WiFiServer(hiddenPort);
  hiddenServer->begin();
  Serial.println("[HIDDEN SERVER] Hidden port ready.");
}

void broadcastMessage() {
  // Construct broadcast message with instructions
  String msg = "Connect via telnet (admin-admin) to " + String(triggerPort) +
               " on 'Mr. Rabbit' from " + triggerIP.toString() +
               " to open hidden port";
  udp.beginPacket(broadcastIP, 5555);  // Send message over UDP port 5555
  udp.print(msg);
  udp.endPacket();
  Serial.println("[BROADCAST] " + msg);
}

void loop() {
  // Periodically broadcast the message
  if (millis() - lastBroadcast > BROADCAST_INTERVAL) {
    lastBroadcast = millis();
    broadcastMessage();
  }

  checkNewConnections();  // Check for new clients
  handleSessions();       // Handle active sessions
}

void checkNewConnections() {
  // Check for new clients on default servers
  for (int i = 0; i < 3; i++) {
    WiFiClient c = defaultServers[i]->available();
    if (c) handleNewClient(c, false);
  }

  // Check for new client on hidden server
  WiFiClient hc = hiddenServer->available();
  if (hc) handleNewClient(hc, true);
}

void handleNewClient(WiFiClient client, bool isHidden) {
  // Accept new connection into available session slot
  for (int i = 0; i < MAX_SESSIONS; i++) {
    if (!sessions[i].client || !sessions[i].client.connected()) {
      sessions[i] = {client, isHidden, millis()};
      client.println("\tWelcome to Mr Rabbit challenge!");
      client.println("Username:");
      return;
    }
  }
  // If no session available
  client.println("Too many connections, try later.");
  client.stop();
}

void handleSessions() {
  for (int i = 0; i < MAX_SESSIONS; i++) {
    TelnetSession& s = sessions[i];
    if (!s.client || !s.client.connected()) continue;

    // Disconnect if session times out
    unsigned long timeout = s.isHidden ? HIDDEN_TIMEOUT : TELNET_TIMEOUT;
    if (millis() - s.startTime > timeout) {
      s.client.println("Session timeout.");
      s.client.stop();
      continue;
    }

    // Read input from client
    if (s.client.available()) {
      String input = s.client.readStringUntil('\n');
      input.trim();

      // If not authenticated yet
      if (!s.authed) {
        if (s.userBuf == "") {
          s.userBuf = input;
          s.client.println("Password:");
        } else if (s.passBuf == "") {
          s.passBuf = input;
          
          // Check credentials for default port (to trigger hidden port)
          if (!s.isHidden &&
              s.client.remoteIP() == triggerIP &&
              s.userBuf == "admin" &&
              s.passBuf == "admin" &&
              s.client.localPort() == triggerPort) {
            s.authed = true;
            hiddenPortOpen = true;
            s.client.println("To complete task connect to the hidden port (" + String(hiddenPort) + ") via telnet with such credentials:");
            s.client.println("Username: " + hiddenUsername);
            s.client.println("Password: " + hiddenPassword);
            s.client.stop();  // Disconnect so user can reconnect to hidden port
          
          // Check credentials for hidden port
          } else if (s.isHidden &&
                     s.userBuf == hiddenUsername &&
                     s.passBuf == hiddenPassword &&
                     s.client.remoteIP() == triggerIP) {
            s.authed = true;
            s.awaitingFullName = true;
            s.client.println("Congratulations!\nYour SECRET WORD: " + secretWord);
            s.client.println("Write your FULL NAME:");
          } else {
            s.client.println("\nInvalid credentials! Try again.");
            s.client.stop(); // Disconnect on invalid credentials
          }
        }
      
      // After successful authentication, collect full name and notify via Telegram
      } else if (s.awaitingFullName) {
        sendTelegramMessage(s.client.remoteIP(), hiddenPort, hiddenUsername, hiddenPassword, input, secretWord);
        s.awaitingFullName = false;
        blinkLed();  // Blink LED as a signal
        delay(5000);
        s.client.println("Message to teacher sent successfully.");
        s.client.stop();
        jump();      // Reboot device
      }
    }
  }
}

void sendTelegramMessage(IPAddress ip, uint16_t port, String user, String pass, String pib, String secret) {
  // Sends collected data to Telegram
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  String url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage";
  String payload = "chat_id=" + CHAT_ID + "&text=" +
                   "🔐 Connection from: " + ip.toString() +
                   "\nMr Rabbit IP: " + WiFi.localIP().toString() +
                   "\nPort: " + String(port) +
                   "\nCredentials: " + user + "/" + pass +
                   "\nFull Name: " + pib +
                   "\nSecret Word: " + secret;

  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(payload);  // Send POST request
  http.end();
  Serial.println("[TELEGRAM] Status: " + String(httpCode));
}

void blinkLed() {
  // Blink LED 10 times
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  }
}

void jump() {
  // Reboot the device to start over
  Serial.println("[JUMP] Restarting to connect to another router...");
  delay(1000);
  ESP.restart();
}
