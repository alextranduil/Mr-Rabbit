# 🐰 Mr. Rabbit
**Mr. Rabbit is a cybersecurity-themed embedded challenge project designed for ESP32. It simulates a stealthy network "target" that participants must discover, connect to, and interact with—much like a CTF (Capture The Flag) game. Participants must use network scanning tools (Nmap, Wireshark) to locate Mr. Rabbit and obtain a secret word.**


## 📋 Requirements
**Hardware:** ESP32 Dev Module, SG90 servo motors, piezo buzzer

**Software:** PlatformIO or Arduino framework, Telegram Bot API token (for notifications)


## 🚀 Getting Started
1. Clone the repo.

2. Set up your parameters:
   + `Secrets.h` - add Wi-Fi SSIDs and passwords
   + `Telegram.h` - insert your Telegram Bot API token and Chat ID

4. Upload to ESP32 using PlatformIO or Arduino IDE.

5. Power on the device. A Telegram message will notify you that Mr. Rabbit is online.


## 🔀 Challenge Flow
### 🟢 Startup
Upon boot, **Mr. Rabbit:**
+ connects randomly to one of the predefined Wi-Fi networks;
+ sends a message via Telegram, plays a buzzer tone, and moves its ears;
+ begins sending packets-messages across the network.

### 🔍 Discovery

Participants must use **Nmap, Wireshark**, or similar tools to:
+ detect Mr. Rabbit’s active IP address,
+ identify open ports,
+ read the broadcast messages containing challenge clues.

### 🔐 Connection

Once discovered, participants connect via **Telnet** to one of the visible ports to receive:
+ hints about the challenge;
+ information about the hidden port;
+ login/password for that hidden port;
+ the final secret keyword upon successful access.

### ⏳ Time Pressure

Mr. Rabbit "jumps" every **10 minutes**, meaning:
+ it connectsto a random Wi-Fi network,
+ a new hidden port is selected,
+ new credentials for the hidden port are generated.

`⏲️ You can adjust the jump interval in Mr_Rabbit.ino by modifying the JUMP_INTERVAL constant.`


## 📁 Task Files
Challenge files for a 5-network setup are available in both Ukrainian and English:

[Mr_Rabbit_Uk.pdf](https://github.com/user-attachments/files/20193534/Mr_Rabbit_Uk.pdf)

[Mr_Rabbit_En.pdf](https://github.com/user-attachments/files/20193235/Mr_Rabbit_En.pdf)


