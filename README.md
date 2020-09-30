# Power Meter

## A) What is it?

It is a current/voltage sensor based on the texas instruments [INA219 current+voltage sensor](https://www.ti.com/product/INA219) and the [ST7789 TFT display](https://www.adafruit.com/product/3787) combined with powerful [ESP32](https://www.espressif.com/en/products/socs/esp32/overview). It can measure voltage, current and power at the same time.

## B) Features

### 1. Captive Portal Webpage

When the ESP32 boots up it acts as a wifi access point and serves a captive portal webpage on address `meter.local` or `192.168.43.1`

![1](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/webpage.png)

### 2. AJAX Based Live Graphs

The live readings are fetched automatically without refreshing the webpage with customizable polling rate!

![2](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/graph.gif)

### 3. Live Readings on a TFT Display

Displays live data on ST7789 TFT display asynchronously.

![3](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/display1.png) ![4](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/display2.png)

### 4. SD Card Support

The data is logged on the SD card in `.CSV` format with timestamps so plotting is easy later. The file is saved as `latest.csv` and the previous session files are automaically renamed so they dont get overridden.

![5](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/csvfile.png)

![6](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/multiplefiles.png)

### 5. Windows app

![7](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/windowsapp.png)

## C) Pin Mapping

Here is a quick look at the pin connection mapping:

#### 1. INA219

| INA219 Pin | ESP32 Pin |
| :--------: | :-------: |
|    VCC     |    3V3    |
|    GND     |    GND    |
|    SCL     |  GPIO22   |
|    SDA     |  GPIO21   |
|    VIN-    |   _N/C_   |
|    VIN+    |   _N/C_   |

#### 2. ST7789

| ST7789 Pin  | ESP32 Pin  |
| :---------: | :--------: |
|     GND     |    3V3     |
|     VCC     |    GND     |
|  SCL (SPI)  |   GPIO22   |
|  SDA (SPI)  |   GPIO21   |
| RES (Reset) |   GPIO4    |
|     D/C     |   GPIO2    |
|   **CS**    | **GPIO15** |
|   **BLK**   |  **3V3**   |

#### **Note:**

If your display **does not have a CS (Chip Select) pin** then you have _two options:_

1.  You have to remove the SD Card circuitary and _optionally_ comment out the SD card code from program.
    This is because the SPI bus is shared between two devices, SD card and the display. For both of them to work, each must have a seperate CS pin.

    **OR**

2.  Modify your display and break out the CS pin. For that, **[follow my guide](https://www.instructables.com/id/Adding-CS-Pin-to-13-LCD/)**.

#### 3. SD Card

| SD Pin | ESP32 Pin |
| :--------: | :-------: |
|    GND     |  VIN(5V)  |
|    VCC     |    GND    |
|    MISO    |  GPIO19   |
|    MOSI    |  GPIO21   |
|    SCK     |  GPIO22   |
|     CS     |  GPIO13   |

## D) Required Libraries/Tools:

1. [Arduino SPIFFS Plugin](https://github.com/me-no-dev/arduino-esp32fs-plugin)
2. [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
3. [TFT_eSPI Library](https://github.com/Bodmer/TFT_eSPI)
4. [Adafruit INA219 Library](https://github.com/adafruit/Adafruit_INA219)
5. [ESP32 AsyncTCP Library](https://github.com/me-no-dev/AsyncTCP)
6. [ESPAsyncWebServer Library](https://github.com/me-no-dev/ESPAsyncWebServer)


![7](https://raw.githubusercontent.com/shreyask21/powermeter/master/img/board.png)