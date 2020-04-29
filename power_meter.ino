#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <SPIFFS.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

TaskHandle_t Task1;
const char* ssid = "Power Meter";
DNSServer dnsServer;
AsyncWebServer server(80);
Adafruit_INA219 ina219;

float voltage, current;
void setup() {
  WiFi.softAP(ssid);
  SPIFFS.begin();
  ina219.begin();
  ina219.setCalibration_32V_2A();
  server.begin();
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });

  server.on("/highcharts.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/highcharts.js", "text/javascript");
  });

  server.on("/dark-unica.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/dark-unica.js", "text/javascript");
  });

  server.on("/voltage", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", getVoltage().c_str());
  });

  server.on("/current", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", getCurrent().c_str());
  });

  server.on("/power", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", getPower().c_str());
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
}

String getVoltage() {
  voltage = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000.0);
  return String(voltage);
}
String getCurrent() {
  current = ina219.getCurrent_mA();
  return String(current);
}
String getPower() {
  getVoltage();
  getCurrent();
  return String(voltage * current);
}

void loop() {
}
