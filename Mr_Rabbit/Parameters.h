#ifndef Parameters_h
#define Parameters_h

#define MAX_SESSIONS 5                 // Maximum allowed concurrent Telnet sessions
#define BROADCAST_INTERVAL 3000        // Interval for sending broadcast messages (in milliseconds)
#define TELNET_TIMEOUT 30000           // Session timeout for standard Telnet ports
#define HIDDEN_TIMEOUT 120000          // Session timeout for hidden port

#define OPEN_PORTS_STRING "23,2323,4242" // SET PORTS HERE (comma-separated string)

#define MAX_OPEN_PORTS 3  // Max allowed open ports

#define MESSAGE_PORT 5555 // the port to which the message is sent

const unsigned long JUMP_INTERVAL = 600000; // Time after which the hidden port and credentials will change

#endif