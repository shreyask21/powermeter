/**
    ESP32 Power Meter
    
    @author Shreyas Kulkarni
    @version 0.1 2020/04/29 
*/

/******************** ESP32 WiFi drivers ********************/
#include <WiFi.h>
#include <SPIFFS.h>

#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

#include <DNSServer.h>
DNSServer dnsServer;
/************************************************************/

/**************** INA219  driver declaration ****************/
#include <Adafruit_INA219.h>
#include <Wire.h>
Adafruit_INA219 INA219;
/************************************************************/

/**************** ST7789 driver declaration *****************/
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold18pt7b.h>
#define TFT_CS  15
#define TFT_RST 4
#define TFT_DC  2
Adafruit_ST7789 TFT = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
/************************************************************/

/******************   WiFi Configuration   ******************/
//#define use_password //<-Uncomment to use password for SoftAP
const char* ssid      =  "Power Meter";
const char* password  =  "password";
/************************************************************/

TaskHandle_t Task1;
float voltage, current;

/************************** SETUP ***************************/
void setup() {
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  INA219.begin();
  INA219.setCalibration_16V_400mA();
  TFT.init(240, 240);
  TFT.setRotation(2);
  TFT.fillScreen(ST77XX_BLACK);
  TFT.setFont(&FreeSansBold18pt7b);
  xTaskCreatePinnedToCore(display_data, "DisplayStask", 10000, NULL, 0, &Task1, 0);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_AP);
#ifdef use_password
  WiFi.softAP(ssid, password);
#else
  WiFi.softAP(ssid);
#endif
  dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
  SPIFFS.begin();
  server.begin();
  addServerHandlers();
}
/************************************************************/

/************************** LOOP ****************************/
void loop() {
  dnsServer.processNextRequest();
}
/************************************************************/

/****************** Read Data From Sensor *******************/
void readSensorData() {
  voltage = INA219.getBusVoltage_V() + (INA219.getShuntVoltage_mV() / 1000.0);
  current = INA219.getCurrent_mA();
}
/************************************************************/

/******************* Display Data To TFT ********************/
void display_data(void * parameter) {
  while (true) {
    readSensorData();
    TFT.setCursor(0, 25);
    TFT.print("V = " + String(voltage)); TFT.println("V");
    TFT.print("I = " + String(current)); TFT.println("mA");
    TFT.print("P = " + String(voltage * current)); TFT.println("mW");
    delay(2000);
  }
}
/************************************************************/

/********* Add Listeners For Server HTTP Requests ***********/
void addServerHandlers() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->redirect("http://meter.local/view");
  });
  server.on("/view", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/voltage", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(voltage).c_str());
  });
  server.on("/current", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(current).c_str());
  });
  server.on("/power", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(voltage * current).c_str());
  });
  server.on("/check", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "ACK");
  });
  server.on("/setcalc", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
    INA219.setCalibration_32V_2A();
  });
  server.on("/setcalb", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
    INA219.setCalibration_32V_1A();
  });
  server.on("/setcala", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
    INA219.setCalibration_16V_400mA();
  });
  server.on("/datahandler.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/datahandler.js", "text/javascript");
  });
  server.on("/graph.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/graph.js", "text/javascript");
  });
  server.on("/theme.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/theme.js", "text/javascript");
  });
  server.on("/meter.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/meter.png", "image/png");
  });
  server.on("/git.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/git.png");
  });
}
/************************************************************/
