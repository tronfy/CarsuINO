#ifndef MICS6814Sensor_h
#define MICS6814Sensor_h

#include "Arduino.h"

// Wrapper for MICS-6814
class MICS6814Sensor
{
  private:
    int coPort, nh3Port, no2Port;
    float maxVolts, maxAnalog;
    bool convertPPM;

  private:
    void getReadings();

  public:
    MICS6814Sensor(int coPort, int nh3Port, int no2Port, float maxVolts, float maxAnalog, bool convertPPM)
    {
      this->coPort = coPort;
      this->nh3Port = nh3Port;
      this->no2Port = no2Port;

      this->maxVolts = maxVolts;
      this->maxAnalog = maxAnalog;
      this->convertPPM = convertPPM;
    }
    void calibrate();
    void package(char *coPkg, char *nh3Pkg, char *no2Pkg);
};
#endif
