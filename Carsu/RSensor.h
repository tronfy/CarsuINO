#ifndef RSensor_h
#define RSensor_h

#include "Arduino.h"

// Generic Resistive Sensor
class RSensor
{
  private:
    char *identifier;
    float resistance;
    int port;
    float volts, maxVolts, maxAnalog, R0, pR0;

  private:
    void getReadings();
    void calibrateStep();

  public:
    RSensor(char *identifier, float resistance, int port, float maxVolts, float maxAnalog)
    {
      this->identifier = new char[10];
      int i = 0;
      while (identifier[i] != '\0' && i < 10)
      {
        this->identifier[i] = identifier[i];
        i++;
      }
      this->identifier[i] = '\0';
      this->resistance = resistance;
      this->port = port;
      this->maxVolts = maxVolts;
      this->maxAnalog = maxAnalog;
    }
    void calibrate();
    void package(char *outPkg);
};
#endif
