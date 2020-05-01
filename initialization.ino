/**
    Starts the drivers in sequence
*/

TaskHandle_t Task1;
bool init_ok = true;
void initialize()
{
  /****************** Start display driver ********************/
  TFT.begin();
  TFT.setRotation(0);
  TFT.fillScreen(TFT_BLACK);
  TFT.setTextColor(TFT_YELLOW, TFT_BLACK);
  TFT.setCursor(0, 0, 4);
  TFT.println("Initializing...");
  printstartuptext("Display", true);
  /************************************************************/

  /******************* Start SPIFFS driver ********************/
  printstartuptext("SPIFFS", SPIFFS.begin());
  /************************************************************/

  /******************* Start INA219 driver ********************/
  printstartuptext("INA219", INA219.begin());
  /************************************************************/

  /****************** Start SD Card driver ********************/
  SD_INSERTED = SD.begin(SD_CS);
  printstartuptext("SD Card", SD_INSERTED == true ? true : 2);
  /************************************************************/

  /*************** Start Rest Of The Program ******************/
  if (init_ok)
  {
    TFT.setTextColor(TFT_GREEN, TFT_BLACK);
    TFT.setCursor(0, 0, 4);
    TFT.println("Initialization OK!");
    TFT.setTextColor(TFT_WHITE, TFT_BLACK);
    delay(3000);
    TFT.fillScreen(TFT_BLACK);
    drawBmp("/splash_screen.bmp", 0, 0);
    delay(5000);
    TFT.fillScreen(TFT_BLACK);
    drawBmp("/background.bmp", 0, 0);
    TFT.setTextDatum(MC_DATUM);
    TFT.setTextPadding(130);
    TFT.setCursor(0, 0, 4);
    INA219.setCalibration_16V_400mA();

    /**************** Pin async task to core 1 ******************/
    xTaskCreatePinnedToCore(display_data, "DisplayStask", 10000, NULL, 1, &Task1, 0);
    /************************************************************/

    /************************ Start WiFi ************************/
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_AP);
#ifdef use_password
    WiFi.softAP(ssid, password);
#else
    WiFi.softAP(ssid);
#endif
    /************************************************************/

    /************* Start HTTP server and DNS server *************/
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
    server.begin();
    addServerHandlers();
    csv_prepare();
    startMillis = millis();
    /************************************************************/
  }
  else
  {
    TFT.println("Program Halted!");
    while (1) {
      yield();
    }
  }
  /************************************************************/

}
/************************************************************/

/**
    Displays the startup text

    @param text The Text to display
    @param status The status of the operation

*/
void printstartuptext(char *text, int status)
{
  if (status == 0)
  {
    TFT.setTextColor(TFT_RED, TFT_BLACK);
    TFT.print("[Err]   ");
    init_ok = false;
  }
  else if (status == 1)
  {
    TFT.setTextColor(TFT_GREEN, TFT_BLACK);
    TFT.print("[OK]   ");
  }
  else if (status == 2)
  {
    TFT.setTextColor(TFT_YELLOW, TFT_BLACK);
    TFT.print("[Warn] ");
  }
  TFT.setTextColor(TFT_WHITE, TFT_BLACK);
  TFT.println(text);
  delay(100);
}
/************************************************************/