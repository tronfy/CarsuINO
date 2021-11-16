#include "QSensor.h"

void QSensor::package(char *outPkg)
{
  float quality = analogRead(port) / maxAnalog * 100;
  sprintf(outPkg, "<%s|%.3f>", identifier, quality);
}
