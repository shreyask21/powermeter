# Power Meter

## What is it?

It is a current/voltage sensor based on the texas instruments [INA219 current+voltage sensor](https://www.ti.com/product/INA219) and the [ST7789 TFT display](https://www.adafruit.com/product/3787) combined with powerful [ESP32](https://www.espressif.com/en/products/socs/esp32/overview). It can measure voltage, current and power at the same time.

## Features

1. Captive Portal Webpage
   When the ESP32 boots up it acts as a wifi access point and serves a captive portal webpage on address `meter.me` or `192.168.1.1`.
   ![1](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/webpage.png)
2. AJAX Based Live Graphs
   The live readings are fetched automatically without refreshing the webpage on a customizable polling rate.
   ![2](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/graph.gif)
3. Live Readings on a TFT Display

## Required Libraries/Tools:

1. [Arduino SPIFFS Plugin](https://github.com/me-no-dev/arduino-esp32fs-plugin)
2. [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
3. [Adafruit ST77XX Library](https://github.com/adafruit/Adafruit-ST7735-Library)
4. [Adafruit INA219 Library](https://github.com/adafruit/Adafruit_INA219)
5. [ESP32 AsyncTCP Library](https://github.com/me-no-dev/AsyncTCP)
6. [ESPAsyncWebServer Library](https://github.com/me-no-dev/ESPAsyncWebServer)
