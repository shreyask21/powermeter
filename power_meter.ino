#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold9pt7b.h>
//#include <Adafruit_PCD8544.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixel
#include <Adafruit_INA219.h>
#define DC 12
#define CE 2
#define RST 0

Adafruit_INA219 ina219;
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);
//Adafruit_PCD8544 display = Adafruit_PCD8544(DC, CE, RST);

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
int power_mW = 0;
void setup() {
  ina219.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  //display.begin();
  //display.setContrast(60);
  display.clearDisplay();
  display.display();
  //display.setTextSize(2);
  display.setFont(&FreeSansBold9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

}

void loop() {
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  display.setCursor(0, 12);
  display.clearDisplay();
  display.print("V = " + String(loadvoltage)); display.println("V");
  display.print("I = " + String(current_mA)); display.println("mA");
  display.print("P = " + String(power_mW)); display.println("mW");
  display.display();
  delay(200);
}
