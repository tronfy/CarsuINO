#include "MICS6814Sensor.h"

void MICS6814Sensor::package(char *coPkg, char *nh3Pkg, char *no2Pkg)
{
  sprintf(coPkg, "<CO|%.3f>", analogRead(coPort) / maxAnalog * 100);
  sprintf(nh3Pkg, "<NH3|%.3f>", analogRead(coPort) / maxAnalog * 100);
  sprintf(no2Pkg, "<NO2|%.3f>", analogRead(coPort) / maxAnalog * 100);
}
