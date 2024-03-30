#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>

// Wifi network station credentials
#define WIFI_SSID "Xiaomi 12T"
#define WIFI_PASSWORD "sebentar"

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "6875247030:AAHpNSRQPzv00sPKdBR3Gl3F4vI-txqs9oU"

#define Irvan_NAME "MUHAMMAD IRVAN"
#define Dhimas_NAME "Dhimas"
#define Maulana_NAME "MMH"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

// Sensor Pins
#define LEDPINUmum D3
#define LEDPINIrvan D0
#define LEDPINDhimas D1
#define LEDPINMaulana D2
#define DHTPIN D5
#define DHTTYPE DHT11 //Mengatur TYPE DHT (Karena ada 2 jenis [DHT11 & DHT22])

float h;
float t;
int ledStatusUmum = 0;
int ledStatusIrvan = 0;
int ledStatusDhimas = 0;
int ledStatusMaulana = 0;

DHT dht(DHTPIN, DHTTYPE);

void handleNewMessages(int numNewMessages) {
  Serial.print("Handle New Messages: ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    h = dht.readHumidity();
    t = dht.readTemperature();
    
    if (text == "/LedUmumOn") {
      digitalWrite(LEDPINUmum, HIGH); // turn the LED on (HIGH is the voltage level)
      ledStatusUmum = 1;
      bot.sendMessage(chat_id, "Led Umum ON", "");
    }

    if (text == "/LedUmumOff") {
      ledStatusUmum = 0;
      digitalWrite(LEDPINUmum, LOW); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led Umum OFF", "");
    }

    if (text == "/LedIrvanOn") {
      if (from_name == Irvan_NAME){
        digitalWrite(LEDPINIrvan, HIGH); // turn the LED on (HIGH is the voltage level)
        ledStatusIrvan = 1;
        bot.sendMessage(chat_id, "Led Irvan ON", "");
      } else if (from_name == Dhimas_NAME){
        bot.sendMessage(chat_id, "Warning!! Dhimas mencoba menyalakan LED Irvan", "");
      } else if (from_name == Maulana_NAME){
        bot.sendMessage(chat_id, "Warning!! Maulana mencoba menyalakan LED Irvan", "");
      } else {
        bot.sendMessage(chat_id, "Anda Tidak Diajak", "");
      }
    }

    if (text == "/LedIrvanOff") {
      if (from_name == Irvan_NAME){
        digitalWrite(LEDPINIrvan, LOW); // turn the LED on (HIGH is the voltage level)
        ledStatusIrvan = 0;
        bot.sendMessage(chat_id, "Led Irvan OFF", "");
      } else if (from_name == Dhimas_NAME){
        bot.sendMessage(chat_id, "Warning!! Dhimas mencoba mematikan LED Irvan", "");
      } else if (from_name == Maulana_NAME){
        bot.sendMessage(chat_id, "Warning!! Maulana mencoba mematikan LED Irvan", "");
      } else {
        bot.sendMessage(chat_id, "Anda Tidak Diajak", "");
      }
    }

    if (text == "/LedDhimasOn") {
      if (from_name == Dhimas_NAME){
        digitalWrite(LEDPINDhimas, HIGH); // turn the LED on (HIGH is the voltage level)
        ledStatusDhimas = 1;
        bot.sendMessage(chat_id, "Led Dhimas ON", "");
      } else if (from_name == Irvan_NAME){
        bot.sendMessage(chat_id, "Warning!! Irvan mencoba menyalakan LED Dhimas", "");
      } else if (from_name == Maulana_NAME){
        bot.sendMessage(chat_id, "Warning!! Maulana mencoba menyalakan LED Dhimas", "");
      } else {
        bot.sendMessage(chat_id, "Anda Tidak Diajak", "");
      }
    }

    if (text == "/LedDhimasOff") {
      if (from_name == Dhimas_NAME){
        digitalWrite(LEDPINDhimas, LOW); // turn the LED on (HIGH is the voltage level)
        ledStatusDhimas = 0;
        bot.sendMessage(chat_id, "Led Dhimas OFF", "");
      } else if (from_name == Irvan_NAME){
        bot.sendMessage(chat_id, "Warning!! Irvan mencoba mematikan LED Dhimas", "");
      } else if (from_name == Maulana_NAME){
        bot.sendMessage(chat_id, "Warning!! Maulana mencoba mematikan LED Dhimas", "");
      } else {
        bot.sendMessage(chat_id, "Anda Tidak Diajak", "");
      }
    }

    if (text == "/LedMaulanaOn") {
      if (from_name == Maulana_NAME){
        digitalWrite(LEDPINMaulana, HIGH); // turn the LED on (HIGH is the voltage level)
        ledStatusMaulana = 1;
        bot.sendMessage(chat_id, "Led Maulana ON", "");
      } else if (from_name == Dhimas_NAME){
        bot.sendMessage(chat_id, "Warning!! Dhimas mencoba menyalakan LED Maulana", "");
      } else if (from_name == Irvan_NAME){
        bot.sendMessage(chat_id, "Warning!! Irvan mencoba menyalakan LED Maulana", "");
      } else {
        bot.sendMessage(chat_id, "Anda Tidak Diajak", "");
      }
    }

    if (text == "/LedMaulanaOff") {
      if (from_name == Maulana_NAME){
        digitalWrite(LEDPINMaulana, LOW); // turn the LED on (HIGH is the voltage level)
        ledStatusMaulana = 0;
        bot.sendMessage(chat_id, "Led Maulana OFF", "");
      } else if (from_name == Dhimas_NAME){
        bot.sendMessage(chat_id, "Warning!! Dhimas mencoba mematikan LED Maulana", "");
      } else if (from_name == Irvan_NAME){
        bot.sendMessage(chat_id, "Warning!! Irvan mencoba mematikan LED Maulana", "");
      } else {
        bot.sendMessage(chat_id, "Anda Tidak Diajak", "");
      }
    }

    if (text == "/ledstatus") {
      String message = "LED Status: \nLed Umum = ";
      if(ledStatusUmum == 1) {
        message += "ON";
      } else {
        message += "OFF";
      }
      message += "\nLed Irvan = ";
      if(ledStatusIrvan == 1) {
        message += "ON";
      } else {
        message += "OFF";
      }
      message += "\nLed Dhimas = ";
      if(ledStatusDhimas == 1) {
        message += "ON";
      } else {
        message += "OFF";
      }
      message += "\nLed Maulana = ";
      if(ledStatusMaulana == 1) {
        message += "ON";
      } else {
        message += "OFF";
      }
      
      bot.sendMessage(chat_id, message, "");
    }
    
    if (text == "/dhtstatus") {
      String message = "";
      message += "Suhu : "+ String(t) + "°C\n";
      message += "Kelembapan : "+ String(h) + " %";
      bot.sendMessage(chat_id, message, "");
    }

    if (text == "/start") {
      String welcome = "Welcome to IoT Telegram Bot, " + from_name + ".\n";
      welcome += "List of Commands:\n\n";
      welcome += "/LedUmumOn : to switch the Led Umum ON\n";
      welcome += "/LedUmumOff : to switch the Led Umum OFF\n";
      welcome += "/LedIrvanOn : to switch the Led Irvan ON\n";
      welcome += "/LedIrvanOff : to switch the Led Irvan OFF\n";
      welcome += "/LedDhimasOn : to switch the Led Dhimas ON\n";
      welcome += "/LedDhimasOff : to switch the Led Dhimas OFF\n";
      welcome += "/LedMaulanaOn : to switch the Led Maulana ON\n";
      welcome += "/LedMaulanaOff : to switch the Led Maulana OFF\n";
      welcome += "/ledstatus : Returns current status of all LED\n";
      welcome += "/dhtstatus : Returns temperature and humidity status of DHT11\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  // Sensor Pin Mode
  pinMode(LEDPINUmum, OUTPUT);
  pinMode(LEDPINIrvan, OUTPUT);
  pinMode(LEDPINDhimas, OUTPUT);
  pinMode(LEDPINMaulana, OUTPUT);
  dht.begin();

  // attempt to connect to Wifi network:
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  // Check NTP/Time, usually it is instantaneous and you can delete the code below.
  Serial.print("Retrieving time: ");
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
    while (numNewMessages) {
      Serial.println("Got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}