// -------- ВРЕМЯ -------
#define GMT 3              // смещение (москва 3)
#define NTP_ADDRESS  "europe.pool.ntp.org"    // сервер времени


// -------- СЕТЬ -------
byte IP[] = {192, 168, 0, 97};
byte subnet[] = {192, 168, 0, 1};
byte gate[] = {255, 255, 255, 0};
#define AP_PORT 8888

// -------- ПИНЫ -------
#define LED_PIN D0   //лента
#define NUM_LEDS 30   //кол-во светодиодов
#define SPQ_PIN D1    //включение колонки
#define BTN1_PIN D2
#define BTN2_PIN D3
#define BTN3_PIN D4
#define BTN_CLICK_TIME 1000

#define RADIO_PIN D5
#define RADIO_VCC D6
#define G433_SPEED 1000
#define RADIO_BUF_SIZE 7

#define DAWNTIME 10
#define DAWNBRIGHT 150

#define MAXSENS 5
#define MAXRULES MAXSENS*2

// ---------------- БИБЛИОТЕКИ -----------------
#define NUM_LEDS 30
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define NTP_INTERVAL 60 * 1000    // обновление (1 минута)

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <FastLED.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "EspMQTTClient.h"
#include <Gyver433.h>

// ------------------- ТИПЫ --------------------
ESP8266WebServer server(80);
CRGB leds[NUM_LEDS];
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, GMT * 3600, NTP_INTERVAL);
Gyver433_RX<RADIO_PIN, RADIO_BUF_SIZE> rx;

EspMQTTClient client(
  "81.177.165.203",
  1883,
  "fifthfloor",
  "root"
);


// ----------------- ПЕРЕМЕННЫЕ ------------------

unsigned int localPort = AP_PORT;
String args;
byte MODEWIFI;

int brightnessls = 30;

byte id = 1;

int enc_state = 0;

boolean nghtlight = 0; // нужно прописать в еепром
int timeonhrs = 0;
int timeonmnts = 0;
int timeoffhrs = 0;
int timeoffmnts = 0;

boolean guard = false;

struct {
  int id = 0;
  int value = 0;
  byte type = 0;
  int timereq = 0;
  byte key = 0;
} sens[MAXSENS];

struct {
  int id = 0;
  bool more = false;
  int value = 0;
  String data = "";
} rules[MAXRULES];

int idS;
String ID_B_S = "";
byte CountSens = 0;
boolean flsens = false;

struct {
  boolean state = false;
  int time;
  boolean sinerise = true;
  int music = 0;
  boolean act = false;
} alarm[5];


unsigned char matrixValue[8][16];
int8_t currentMode = 2;
String lampIP = "";
char ssid[15] = "";
String ssidStr = "";
char pass[15] = "";
String passStr = "";
char secret[5] = "";
String secretStr = "";
void(* resetFunc) (void) = 0;
int error = 0;
byte volume = 55;
boolean speaker = false;
boolean mqtt = false;

int r = 254;
int g = 224;
int b = 0;


boolean fl = false;

uint32_t eepromTimer;
int timevalue;
byte days;

byte counter;
int timer = 0;



void setup() {
  //  pinMode(2, OUTPUT);
  pinMode(BTN1_PIN, INPUT);
  pinMode(BTN2_PIN, INPUT);
  pinMode(BTN3_PIN, INPUT);

  defRules();

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
  FastLED.setBrightness(0);
  FastLED.show();
  pinMode(RADIO_VCC, OUTPUT);
  digitalWrite(RADIO_VCC, HIGH);
  //  pinMode(SPQ_PIN, OUTPUT);
  //  digitalWrite(SPQ_PIN, LOW);
  Serial.begin(9600);
  EEPROM.begin(50);
  delay(50);
  MODEWIFI = EEPROM.read(0);
  delay(50);
  ID_B_S = (String) ((byte) EEPROM.read(1));
  delay(50);
  if (MODEWIFI == 1) {

    WiFi.disconnect();
    for (byte i = 2; i < 17; i++) {
      ssidStr += (char) EEPROM.read(i);
      delay(50);
      passStr += (char) EEPROM.read(i + 15);
    }
    passStr.toCharArray(pass, passStr.length());
    ssidStr.toCharArray(ssid, ssidStr.length());
    const char* autoConnectSSID = ssid;
    const char* autoConnectPass = pass;
    Serial.print("ssid: ");
    Serial.println(autoConnectSSID);
    Serial.print("password: ");
    Serial.println(autoConnectPass);

    WiFi.mode(WIFI_STA);
    WiFi.begin(autoConnectSSID, autoConnectPass);
    delay(500);
    for (byte i = 32; i < 37; i++) {
      secretStr += (char) EEPROM.read(i);
      delay(50);
    }
    Serial.println(secretStr);
  } else {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Torsher", "12345678");
    //    WiFi.softAPConfig(IPAddress(IP[0], IP[1], IP[2], IP[3]),
    //                      IPAddress(IP[0], IP[1], IP[2], IP[3]),
    //                      IPAddress(255, 255, 255, 0));
    delay(500);
  }


  if (MODEWIFI == 1) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(200);
    }
    Serial.println("Connected to WiFi! IP address: " + WiFi.localIP().toString());
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
  } else {
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("Connected to AP! IP address: ");
    Serial.println(myIP);
  }

  timeClient.begin();
  timeClient.update();

  timevalue = (timeClient.getHours() * 60 + timeClient.getMinutes()) * 60 + timeClient.getSeconds();
  server.enableCORS(true);
  server.on("/a", handleRoot);
  server.begin();
  //  Serial.println("New IP address: " + WiFi.localIP().toString());
  FastLED.setBrightness(brightnessls);
  FastLED.show();
}


void loop() {
  server.handleClient();
  client.loop();
  sttTick();
  time_tick();
  button_tick();
  // effect_tick();
  //  lightmusic(2);
  // ring_ticker();
  sensor_tick();
  // //  if(volume!=0) digitalWrite(SPQ_PIN, HIGH); else digitalWrite(SPQ_PIN, LOW);
}
