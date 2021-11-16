#include "RSensor.h"

#define SAMPLE_GAP 5000

void RSensor::getReadings()
{
  volts = analogRead(port) / maxAnalog * maxVolts;
}

void RSensor::calibrateStep()
{
  getReadings();
  pR0 = R0;
  R0 = ((maxVolts * resistance) / volts) - resistance;
}

void RSensor::calibrate()
{
  Serial.print("Calibrando ");
  Serial.print(identifier);
  Serial.print("... ");
  do
  {
    delay(SAMPLE_GAP);
    calibrateStep();
  } while ((int)pR0 - (int)R0 > 2);
  Serial.print("OK R0 = ");
  Serial.println(R0);
}

void RSensor::package(char *outPkg)
{
  float value = analogRead(port) / maxAnalog * 100;
  // float volts = analogRead(port) / maxAnalog * maxVolts;
  // value = pow(1538.46 * (maxVolts - volts) / volts / R0, -1.709);
  sprintf(outPkg, "<%s|%.3f>", identifier, value);
}
