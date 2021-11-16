#ifndef RSensor_h
#define RSensor_h

#include "Arduino.h"

// Generic Resistive Sensor
class RSensor
{
  private:
    char *gas;
    float resistance;
    int port;
    float volts, maxVolts, maxAnalog, R0, pR0;
    float a, b;
    bool convertPPM;

  private:
    void getReadings();
    void calibrateStep();

  public:
    RSensor(char *gas, float resistance, int port, float maxVolts, float maxAnalog, float a, float b, bool convertPPM)
    {
      this->gas = new char[10];
      int i = 0;
      while (gas[i] != '\0' && i < 10)
      {
        this->gas[i] = gas[i];
        i++;
      }
      this->gas[i] = '\0';
      this->resistance = resistance;
      this->port = port;
      this->maxVolts = maxVolts;
      this->maxAnalog = maxAnalog;
      this->a = a;
      this->b = b;
      this->convertPPM = convertPPM;
    }
    void calibrate();
    void package(char *outPkg);
};
#endif
