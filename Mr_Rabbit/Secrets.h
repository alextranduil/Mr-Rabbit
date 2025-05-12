#ifndef Secrets_h
#define Secrets_h

#define MAX_SESSIONS 5                  // Maximum allowed concurrent Telnet sessions
#define BROADCAST_INTERVAL 3000        // Interval for sending broadcast messages (in milliseconds)
#define TELNET_TIMEOUT 30000           // Session timeout for standard Telnet ports
#define HIDDEN_TIMEOUT 120000           // Session timeout for hidden port

// Arrays to store multiple Wi-Fi credentials
const char* ssids[] = {
// here write ssids of your WiFi routers (separated by comma)
};

const char* passwords[] = {
// here write passwords of your WiFi routers in the same order (separated by comma)
};

#endif