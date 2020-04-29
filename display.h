#include "Arduino.h"

class Display
{
  private:
    int brightness = 0;
  public:
    void displayReadings(String voltage, String current, String power);

    void init();

    void displayRange(String range);
};
