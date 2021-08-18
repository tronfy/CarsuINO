#include "Sensor.h"

#define CALIB_INTER 5000
#define CALIB_STAND 10000

void Sensor::getReadings() {
  volts = analogRead(port) / 1024.0 * 5.0;
}

void Sensor::calibrateStep() {
  getReadings();
  pR0 = R0;
  R0 = ((5.0 * resistance) / volts) - resistance;
}

void Sensor::calibrate() {
  Serial.print("Calibrating ");
  Serial.print(gas);
  Serial.print(" sensor... ");
  delay(CALIB_STAND);
  do {
    delay(CALIB_INTER);
    calibrateStep();
  } while ((int)pR0 != (int)R0);
  Serial.println("done");
}

String Sensor::package() {
  getReadings();
  float ppm = pow(1538.46 * (5.0 - volts) / volts / R0, -1.709);
  
  String str = gas;
  str.concat("|");
  str.concat(ppm);
  String pkg = "<" + String(str) + ">";
  return pkg;
}
