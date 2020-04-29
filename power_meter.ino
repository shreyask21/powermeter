#include "currentSensor.h"
#include "display.h"

CurrentSensor sensor;
Display display;

void setup()
{
  display.init();
  sensor.init();
}

void loop()
{
  sensor.takeReading();
  display.displayReadings(sensor.voltage, sensor.current, sensor.power);
  delay(200);
}
