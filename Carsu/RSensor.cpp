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
  Serial.print("Calibrating ");
  Serial.print(gas);
  Serial.print(" sensor... ");
  do
  {
    delay(SAMPLE_GAP);
    calibrateStep();
  } while ((int)pR0 - (int)R0 > 2);
  Serial.print("done. R0 = ");
  Serial.println(R0);
}

void RSensor::package(char *outPkg)
{
  float value = analogRead(port) / maxAnalog * 100;
  if (convertPPM) {
    float volts = analogRead(port) / maxAnalog * maxVolts;
    value = pow(a * (maxVolts - volts) / volts / R0, b);
  }
  sprintf(outPkg, "<%s|%.3f>", gas, value);
}
