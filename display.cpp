#include "display.h"
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI driver = TFT_eSPI();

void Display::init()
{
  driver.init();
  driver.fillScreen(TFT_WHITE);
  delay(5000);
  driver.fillScreen(TFT_BLACK);
  driver.setTextColor(TFT_WHITE, TFT_BLACK);
  driver.setCursor(0, 0, 5);
  driver.println("TEST");
  driver.setTextColor(TFT_BLACK, TFT_WHITE);
  driver.println("TEST");
  delay(6000);
  driver.fillScreen(TFT_BLACK);
}

void Display::displayReadings(String voltage, String current, String power)
{
  driver.setCursor(5, 15, 5);
  driver.print("V");
  driver.setCursor(18, 15, 5);
  driver.print(":");
  driver.setCursor(25, 15, 5);
  driver.print(voltage);

  driver.setCursor(5, 37, 5);
  driver.print("I");
  driver.setCursor(18, 37, 5);
  driver.print(":");
  driver.setCursor(25, 37, 5);
  driver.print(current);

  driver.setCursor(5, 57, 5);
  driver.print("P");
  driver.setCursor(18, 57, 5);
  driver.print(":");
  driver.setCursor(25, 57, 5);
  driver.print(power);
}

void Display::displayRange(String range)
{
  driver.setCursor(0, 12, 5);
  driver.fillScreen(TFT_BLACK);
  driver.println("Range");
  driver.println(range);
}
