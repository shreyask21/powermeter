int checkSD() {
  SD_INSERTED = SD.begin(SD_CS);
  SD_INSERTED &= (SD.totalBytes() - SD.usedBytes() > 1024 * 1000 * 100);
  SD_INSERTED &= SD.cardType() != CARD_NONE;
  return SD_INSERTED ? 1 : 2;
}

void ejectSD() {
  TFT.fillScreen(TFT_BLACK);
  drawBmp("/sdicon.bmp", 0, 0);
  TFT.setTextDatum(MC_DATUM);
  if (SD_INSERTED) {
    SD.end();
    SD_INSERTED = false;
    TFT.setCursor(70, 120, 4);
    TFT.setTextColor(TFT_GREEN, TFT_WHITE);
    TFT.println("EJECTED");
  } else {
    if (checkSD() == 1) {
      SD_INSERTED = true;
      TFT.setTextColor(TFT_GREEN, TFT_WHITE);
      TFT.setCursor(100, 120, 4);
      TFT.println("OK");
      TFT.setCursor(56, 177, 4);
      TFT.printf("Size: %llu GiB", SD.cardSize() / (1073741824));
      csv_prepare();
    } else {
      SD_INSERTED = false;
      TFT.setTextColor(TFT_RED, TFT_WHITE);
      TFT.setCursor(115, 120, 4);
      TFT.println("?");
    }
  }
  delay(3000);
  TFT.fillScreen(TFT_BLACK);
  TFT.setCursor(0, 0, 4);
  drawBmp("/background.bmp", 0, 0);
  SD_EJECT_REQEST = false;
}

void ejectISR() {
  SD_EJECT_REQEST = true;
}
