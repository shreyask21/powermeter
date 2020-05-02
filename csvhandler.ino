void csv_prepare() {
  if (SD_INSERTED) {
    startMillis = millis();
    String newfilename;
    uint32_t filecounter = 0;
    File root = SD.open("/");
    File CSVFile = SD.open("/latest.csv");
    if (CSVFile && !CSVFile.isDirectory()) {
      File tmpfile = root.openNextFile();
      tmpfile = root.openNextFile(); //Open first file in root
      tmpfile = root.openNextFile(); //Start from second file, ignore first file.
      while (tmpfile) {
        if (!tmpfile.isDirectory()) {
          filecounter++;
        }
        tmpfile = root.openNextFile();
      }
      tmpfile.close();
      newfilename = "/old_" + String(filecounter) + ".csv";
      tmpfile = SD.open(newfilename.c_str());
      if (tmpfile) {
        while (tmpfile) {
          filecounter++;
          newfilename = "/old_" + String(filecounter) + ".csv";
          tmpfile = SD.open(newfilename.c_str());
        }
      }
      tmpfile.close();
      SD.rename("/latest.csv", newfilename.c_str());
    }
    root.close();
    CSVFile.close();
    CSVFile = SD.open("/latest.csv", FILE_WRITE);
    CSVFile.println("Power (mW), Voltage (V), Current (mA), Time (s)");
    CSVFile.close();
  }
}

void csv_write(float power, float voltage, float current) {
  if (SD_INSERTED && !SERVER_BUSY) {
    SD_BUSY = true;
    File CSVFile = SD.open("/latest.csv", FILE_APPEND);
    String data = String(power, 3) + "," + String(voltage, 3)
                  + "," + String(current, 3) + ","
                  + String((((float)millis() - (float)startMillis) / (float)1000), 3);
    CSVFile.println(data.c_str());
    CSVFile.close();
    SD_BUSY = false;
  }
}
