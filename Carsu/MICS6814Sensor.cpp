#include "MICS6814Sensor.h"

void MICS6814Sensor::calibrate()
{
  Serial.print("Calibrating MICS-6814... ");
  Serial.println("not implemented");
}

void MICS6814Sensor::package(char *coPkg, char *nh3Pkg, char *no2Pkg)
{
  if (convertPPM) {
    sprintf(coPkg, "<CO|%.3f>", 0);
    sprintf(nh3Pkg, "<NH3|%.3f>", 0);
    sprintf(no2Pkg, "<NO2|%.3f>", 0);
  } else {
    sprintf(coPkg, "<CO|%.3f>", analogRead(coPort) / maxAnalog * 100);
    sprintf(nh3Pkg, "<NH3|%.3f>", analogRead(coPort) / maxAnalog * 100);
    sprintf(no2Pkg, "<NO2|%.3f>", analogRead(coPort) / maxAnalog * 100);
  }
}
