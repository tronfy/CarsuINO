#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor
{
  private:
    char* gas;
    float resistance;
    int port;
    float volts, R0, pR0;
  private:
    void getReadings();
    void calibrateStep();
  public:
    Sensor(char* gas, float resistance, int port) {
      this -> gas = new char[10];
      int i = 0;
      while(gas[i] != '\0' && i < 10) {
        this -> gas[i] = gas[i];
        i++;
      }
      this -> gas[i] = '\0';
      this -> resistance = resistance;
      this -> port = port;
    }
    void calibrate();
    void package(char* outPkg);
};
#endif
