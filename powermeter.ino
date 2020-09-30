/**
    ESP32 Power Meter

    @author Shreyas Kulkarni
    @version 0.1.1 2020/04/30
*/

/******************** ESP32 WiFi drivers ********************/
#include <WiFi.h>

#define FS_NO_GLOBALS
#include <SPIFFS.h>

#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);
bool SERVER_BUSY = false;

#include <DNSServer.h>
DNSServer dnsServer;
/************************************************************/

/**************** INA219  driver declaration ****************/
#include <Adafruit_INA219.h>
#include <Wire.h>
Adafruit_INA219 INA219;
/************************************************************/

/**************** SD Card driver declaration ****************/
#include <FS.h>
#include <SD.h>
#define SD_CS 13
bool SD_INSERTED = false;
bool SD_EJECT_REQEST = false;
bool SD_BUSY = false;
/************************************************************/

/**************** ST7789 driver declaration *****************/
#include <TFT_eSPI.h>
TFT_eSPI TFT = TFT_eSPI();
/********************* TFT_eSPI config **********************/
/*************  Use Setup24_ST7789.h ****************/
// #define TFT_WIDTH  240
// #define TFT_HEIGHT 240
// #define TFT_MISO 19
// #define TFT_MOSI 23
// #define TFT_SCLK 18
// #define TFT_CS    15
// #define TFT_DC    2
// #define TFT_RST   4
/****************************************************/
/************************************************************/

/******************   WiFi Configuration   ******************/
//#define use_password //<-Uncomment to use password for SoftAP
const char *ssid = "Power Meter";
const char *password = "password";
/************************************************************/

/***********************   Variables   **********************/
volatile float voltage, current, power, charge, energy;
unsigned long startMillis, currentMillis;
String data_string;
/************************************************************/

/************************** SETUP ***************************/
void setup()
{
  initialize();
}
/************************************************************/

/************************** LOOP ****************************/
void loop()
{
  dnsServer.processNextRequest();
  if (SD_EJECT_REQEST) {
    ejectSD();
  } else {
    readSensorData();
    TFT.setTextDatum(MR_DATUM);
    TFT.setTextPadding(100);
    TFT.setTextColor(0x059E, TFT_BLACK);
    TFT.drawFloat(voltage, 3, 228, 26);
    TFT.setTextColor(0xF800, TFT_BLACK);
    TFT.drawFloat(current, 3, 228, 73);
    TFT.setTextColor(0xC81F, TFT_BLACK);
    TFT.drawFloat(power, 3, 228, 121);
    TFT.setTextColor(0x058A, TFT_BLACK);
    TFT.drawFloat(charge, 3, 228, 167);
    TFT.setTextColor(0xFE00, TFT_BLACK);
    TFT.drawFloat(energy, 3, 228, 215);
    send_serial_data();
    csv_write();
    delay(500);
  }
}
/************************************************************/

/****************** Read Data From Sensor *******************/
void readSensorData()
{
  currentMillis = millis();
  voltage = INA219.getBusVoltage_V() + (INA219.getShuntVoltage_mV() / 1000.0);
  current = INA219.getCurrent_mA();
  power   = voltage * current;
  power   = power < 0 ? -power : power;
  charge += current / 7200;
  energy += power / 7200;
  data_string = String(voltage, 3)
                + "," + String(current, 3)
                + "," + String(power,   3)
                + "," + String(charge,  3)
                + "," + String(energy,  3)
                + "," + String((float)((currentMillis - startMillis) / (float)1000.0), 3);
}
/************************************************************/
