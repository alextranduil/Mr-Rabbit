# 🐰 Mr. Rabbit
**Mr. Rabbit is a cybersecurity-themed embedded challenge project designed for ESP32. It simulates a stealthy network "target" that participants must discover, connect to, and interact with—much like a CTF (Capture The Flag) game. Participants must use network scanning tools (Nmap, Wireshark) to locate Mr. Rabbit and obtain a secret word.**


## 📋 Requirements
**Hardware:** ESP32 (Dev Module), SG90 servo motors, piezo buzzer

**Software:** PlatformIO or Arduino framework, Telegram Bot API token (for notifications)


## 🚀 Getting Started
1. Clone the repo.

2. Set up your parameters:
   + `Secrets.h` - add Wi-Fi SSIDs and passwords; fill in Telegram Bot API token and Chat ID
   + `Parameters.h` - you can set ports, telnet parameters or leave default settings

4. Upload to ESP32 using PlatformIO or Arduino IDE.

5. Power on the device. A Telegram message will notify you that Mr. Rabbit is online.

   ![Mr_Rabbit_starting](https://github.com/user-attachments/assets/bbbe1ef5-638c-4562-aa92-7e7bf9ffa079)


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

## 🧠 How to solve Mr Rabbit Challange

+ **Find the real IP address of the device using Nmap:**

  ![nmap](https://github.com/user-attachments/assets/6ad2d861-9563-434b-a733-5eca6ed32bc2)

+ **Find the port on which Mr. Rabbit is waiting for a friend:**
  - Yes:

    ![true_rabbit](https://github.com/user-attachments/assets/ec75efb8-4d49-4b6a-87dd-8ca11ed4c821)

  - No:

    ![fake_rabbbit](https://github.com/user-attachments/assets/fb829639-1755-41b0-b863-d07fbb11c523)

+ **Discover the friend's IP (via Wireshark) and change the adapter settings to this IP:**

  ![wireshark](https://github.com/user-attachments/assets/d6feb207-1dca-4fee-9fb3-c931dad9ecd4)

+ **Connect to the port on which Mr. Rabbit is waiting for a friend, and authenticate with the login "rabbit" and the password "carrot". Obtain the hidden port, login, and password:**

  ![hello_friend](https://github.com/user-attachments/assets/76cfffa9-8e6c-4f9c-bc6b-e6b5ee66c339)

+ **Connect to the hidden port, enter the obtained login and password. Enter your full name. Obtain the secret word-nickname (for example: RABBIT52891):**

  - Successesfull solving:
    
    ![congratulations_rabbit](https://github.com/user-attachments/assets/aa405dfc-ebf5-4470-8848-d0f460a8c9a8)
  - Message in Telegram about successful completion:
    
    ![success_message](https://github.com/user-attachments/assets/c31989ab-e777-4647-a76d-fb0a5e43a78d)


