#include "BluetoothSerial.h"
#include "MICS6814Sensor.h"
#include "RSensor.h"
#include "QSensor.h"

#define MAX_VOLTS 3.3
#define MAX_ANALOG 4095.0
#define PREHEAT_STANDBY 10000

BluetoothSerial SerialBT;

// identifier, resistance, port, maxVolts, maxAnalog
RSensor MQ7("MQ7", 2000, 26, MAX_VOLTS, MAX_ANALOG);

// coPort, nh3Port, no2Port, maxVolts, maxAnalog
MICS6814Sensor MICS6814(13, 12, 14, MAX_VOLTS, MAX_ANALOG);

// identifier, port, maxAnalog
QSensor MQ135("MQ135", 27, MAX_ANALOG);

char co7Pkg[18];

char coPkg[18];
char nh3Pkg[18];
char no2Pkg[18];

char mq135Pkg[18];

void setup()
{
  Serial.begin(115200);
  Serial.println("SERIAL OK");

  SerialBT.begin("Carsu");
  Serial.println("BLUETOOTH OK");

  Serial.print("Preaquecendo... ");
  delay(PREHEAT_STANDBY);
  Serial.println("OK");

  MQ7.calibrate();
}

void sendBT(char *d)
{
  Serial.print("<< BT ");
  Serial.println(d);
  SerialBT.print(d);
}

void recvBT()
{
  if (SerialBT.available())
  {
    Serial.print("BT >> ");

    while (SerialBT.available())
      Serial.write(SerialBT.read());

    Serial.println();
  }
}

void loop()
{
  char pkg[128];

  MQ7.package(co7Pkg);
  MICS6814.package(coPkg, nh3Pkg, no2Pkg);

  MQ135.package(mq135Pkg);

  sprintf(pkg, "%s %s %s %s %s", co7Pkg, coPkg, nh3Pkg, no2Pkg, mq135Pkg);
  sendBT(pkg);

  recvBT();
  delay(500);
}
