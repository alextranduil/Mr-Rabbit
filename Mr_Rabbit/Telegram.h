#ifndef Telegram_h
#define Telegram_h

const String BOT_TOKEN = "";       // Telegram bot token (fill in)
const String CHAT_ID   = "";          // Telegram chat ID to send messages to (fill in)


// sending message of successfull solving via Telegram
void sendTelegramMessage(IPAddress ip, uint16_t port, String user, String pass, String pib, String secret) {
  if (WiFi.status() != WL_CONNECTED) return;
  HTTPClient http;
  String url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage";
  String payload = "chat_id=" + CHAT_ID + "&text=" +
                   "🎩 Mr. Rabbit Challenge Completed!" + 
                   "\nConnection from: " + ip.toString() +
                   "\nMr Rabbit IP: " + WiFi.localIP().toString() +
                   "\nPort: " + String(port) +
                   "\nCredentials: " + user + "/" + pass +
                   "\nFull Name: " + pib +
                   "\nSecret Word: " + secret;

  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(payload);
  http.end();
}

// send message about start of Mr. Rabbit
void sendTelegramStart(IPAddress ip) {
  HTTPClient http;
  String url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage";
  String payload = "chat_id=" + CHAT_ID + "&text=" + "🐰 Mr. Rabbit IP: " + ip.toString();

  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(payload);
  http.end();
}

#endif