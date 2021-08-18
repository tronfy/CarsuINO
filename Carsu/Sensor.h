#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor
{
  private:
    String gas;
    float resistance;
    int port;
    float volts, R0, pR0;
  private:
    void getReadings();
    void calibrateStep();
  public:
    Sensor(String gas, float resistance, int port) {
      this -> gas = gas;
      this -> resistance = resistance;
      this -> port = port;
    }
    void calibrate();
    String package();
};
#endif
