#include "Arduino.h"

class CurrentSensor
{
  public:
    String voltage;
    String current;
    String power;

    void takeReading();

    void init();

};
