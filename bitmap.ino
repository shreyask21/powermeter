/**
    Displays the bitmap file from SPIFFS

    @param filename The name of the file in SPIFFS
    @param x The 'X' co-ordinate of the starting point on display
    @param y The 'Y' co-ordinate of the starting point on display

*/
void drawBmp(const char *filename, int16_t x, int16_t y)
{
  if ((x >= TFT.width()) || (y >= TFT.height()))
    return;
  fs::File bmpFS;
  bmpFS = SPIFFS.open(filename, "r");
  if (!bmpFS)
  {
    Serial.print("File not found");
    return;
  }
  uint32_t seekOffset;
  uint16_t w, h, row, col;
  uint8_t r, g, b;
  uint32_t startTime = millis();
  if (read16(bmpFS) == 0x4D42)
  {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0))
    {
      y += h - 1;
      bool oldSwapBytes = TFT.getSwapBytes();
      TFT.setSwapBytes(true);
      bmpFS.seek(seekOffset);
      uint16_t padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3 + padding];
      for (row = 0; row < h; row++)
      {
        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t *bptr = lineBuffer;
        uint16_t *tptr = (uint16_t *)lineBuffer;
        for (uint16_t col = 0; col < w; col++)
        {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }
        TFT.pushImage(x, y--, w, 1, (uint16_t *)lineBuffer);
      }
      TFT.setSwapBytes(oldSwapBytes);
      Serial.print("Loaded in ");
      Serial.print(millis() - startTime);
      Serial.println(" ms");
    }
    else
      Serial.println("BMP format not recognized.");
  }
  bmpFS.close();
}
/************************************************************/

uint16_t read16(fs::File &f)
{
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(fs::File &f)
{
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
