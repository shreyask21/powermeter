#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <SPIFFS.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_INA219.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold9pt7b.h>

Adafruit_INA219 ina219;
Adafruit_SSD1306 display(128, 64, &Wire, 4);
AsyncWebServer server(80);
DNSServer dnsServer;
const char* ssid = "Power Meter";
float voltage, current;
TaskHandle_t Task1;

void readSensorData() {
  voltage = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000.0);
  current = ina219.getCurrent_mA();
}

void display_data(void * parameter) {
  while (true) {
    readSensorData();
    display.setCursor(0, 12);
    display.clearDisplay();
    display.print("V = " + String(voltage)); display.println("V");
    display.print("I = " + String(current)); display.println("mA");
    display.print("P = " + String(voltage * current)); display.println("mW");
    display.display();
    delay(200);
  }
}

void setup() {
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  ina219.begin();
  ina219.setCalibration_32V_2A();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(0);
  display.clearDisplay();
  display.display();
  display.setFont(&FreeSansBold9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  xTaskCreatePinnedToCore(display_data, "DisplayStask", 10000, NULL, 0, &Task1, 0);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
  SPIFFS.begin();
  server.begin();
  addServerHandlers();
}

void addServerHandlers() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("http://meter.me/view");
  });
  
  server.on("/view", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });

  server.on("/datahandler.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/datahandler.js", "text/javascript");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
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

  server.on("/voltage", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(voltage).c_str());
  });

  server.on("/current", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(current).c_str());
  });

  server.on("/power", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(voltage * current).c_str());
  });

  server.on("/setcalc", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
    ina219.setCalibration_32V_2A();
  });

  server.on("/setcalb", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
    ina219.setCalibration_32V_1A();
  });

  server.on("/setcala", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
    ina219.setCalibration_16V_400mA();
  });
  
  server.on("/git.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/git.png");
  });
}

void loop() {
  dnsServer.processNextRequest();
}
