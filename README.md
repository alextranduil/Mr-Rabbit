# 🐰 Mr. Rabbit
**Mr. Rabbit is a cybersecurity-themed embedded challenge project designed for ESP32. It simulates a stealthy network "target" that participants must discover, connect to, and interact with—much like a CTF (Capture The Flag) game. Participants must use network scanning tools (Nmap, Wireshark) to locate Mr. Rabbit and obtain a secret word.**


## 📡 Requirements
**Hardware:** ESP32 Dev Module, SG90 servo motors, piezo buzzer

**Software:** PlatformIO or Arduino framework, Telegram Bot API token (for notifications)


## 🚀 Getting Started
1. Clone the repo.

2. Set up your parameters in Secrets.h (WiFi ssids/passwords) and Telegram.h (Telegram Bot API token, Telegram Chat ID)

3. Upload to ESP32 via PlatformIO or Arduino IDE.

4. Power up the device and see the message in Telegram that Mr. Rabbit is on.


## 🧪 Challenge Flow
### Startup
**Mr. Rabbit:**
+ connects to one of the predefined Wi-Fi networks randomly;
+ sends message in Telegram, gives sound and moves ears;
+ starts sending packets-messages in the network.

### Discovery

Participants must use **Nmap, Wireshark**, or similar tools to scan the network and detect the active IP, open ports of Mr. Rabbit and message that it sends.

### Connection

Once found, users connect via **Telnet** to retrieve:
+ hints about the challenge;
+ hints about hidden port;
+ login/password for hidden port;
+ secret key-word.

### Time Pressure

Mr. Rabbit jumps (change WiFi, hidden port and secrets) every 10 minutes (you can change this time in the Mr_Rabbit.ino - JUMP_INTERVAL), so be quick.


