File CSVFile;
int interval = 0;

void csv_prepare() {
  if (SD_INSERTED) {
    startMillis = millis();
    String newfilename;
    uint32_t filecounter = 0;
    File root = SD.open("/");
    CSVFile = SD.open("/latest.csv");
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
    CSVFile.println("Voltage (V), Current (mA), Power (mW), Charge (mAh), Energy (mWh), Time (s)");
    CSVFile.close();
    CSVFile = SD.open("/latest.csv", FILE_APPEND);
  }
}

void csv_write() {
  if (SD_INSERTED && !SERVER_BUSY) {
    SD_BUSY = true;
    CSVFile = SD.open("/latest.csv", FILE_APPEND);
    CSVFile.println(data_string.c_str());
    CSVFile.close();
    SD_BUSY = false;
  }
}
