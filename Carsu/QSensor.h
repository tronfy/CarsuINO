#ifndef QSensor_h
#define QSensor_h

#include "Arduino.h"

// Generic Quality Sensor
class QSensor
{
  private:
    char *identifier;
    int port;
    float maxAnalog;

  public:
    QSensor(char *identifier, int port, float maxAnalog)
    {
      this->identifier = new char[10];
      int i = 0;
      while (identifier[i] != '\0' && i < 10)
      {
        this->identifier[i] = identifier[i];
        i++;
      }
      this->identifier[i] = '\0';
      this->port = port;
      this->maxAnalog = maxAnalog;
    }
    void package(char *outPkg);
};
#endif
