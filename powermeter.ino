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
float voltage, current, power;
unsigned long startMillis;
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
}
/************************************************************/

/****************** Read Data From Sensor *******************/
void readSensorData()
{
  voltage = INA219.getBusVoltage_V() + (INA219.getShuntVoltage_mV() / 1000.0);
  current = INA219.getCurrent_mA();
  power   = INA219.getPower_mW();
}
/************************************************************/

/******************* Display Data To TFT ********************/
void display_data(void *parameter)
{
  while (true)
  {
    if (SD_EJECT_REQEST) {
      ejectSD();
    } else {
      readSensorData();
      TFT.setTextColor(0xCB3E, TFT_BLACK);
      TFT.drawFloat(power, 3, 120, 53);
      TFT.setTextColor(0x3CDF, TFT_BLACK);
      TFT.drawFloat(voltage, 3, 120, 133);
      TFT.setTextColor(0xC826, TFT_BLACK);
      TFT.drawFloat(current, 3, 120, 210);
      csv_write(power, voltage, current);
      delay(200);
    }
  }
}
/************************************************************/
