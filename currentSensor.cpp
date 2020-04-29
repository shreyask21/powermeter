#include "currentSensor.h"
#include "display.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
Display disp;


void CurrentSensor::takeReading()
{
  float curr = ina219.getCurrent_mA();
  float vol = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000.0);
  double pow = vol * curr;
  char* volt_str;
  
  //sprintf(volt_str, "%02.2f", vol);
  voltage = String(vol) + "V";
  current = curr > 1000.0 ? String(curr / 1000.0) + "A" : String(curr) + "mA";
  power = pow > 1000.0 ? String(pow / 1000.0) + "W" : String(pow) + "mW";
}

void CurrentSensor::init()
{
  ina219.begin();
  ina219.setCalibration_32V_2A();
}
