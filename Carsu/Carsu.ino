#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "MICS6814Sensor.h"
#include "RSensor.h"
#include "QSensor.h"

#define MAX_VOLTS       3.3
#define MAX_ANALOG      4095.0
#define PREHEAT_STANDBY 10000

#define CARSU_UUID "7f69779e-1f87-4808-9988-b13f959ee8ad"
#define READINGS_UUID "755a2383-32be-4ae2-b19b-b68ad97d9d5a"

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pReadings;

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

  BLEDevice::init("Carsu");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(CARSU_UUID);

  pReadings = pService->createCharacteristic(READINGS_UUID, BLECharacteristic::PROPERTY_READ);
  pReadings->setValue("<init|0.000>");
  pService->start();

  // BLEAdvertising *pAdvertising = pServer->getAdvertising();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(CARSU_UUID);
  // pServer->getAdvertising()->start();
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);

  BLEDevice::startAdvertising();
  Serial.println("BLUETOOTH OK");

  Serial.print("Preaquecendo... ");
  //delay(PREHEAT_STANDBY);
  Serial.println("OK");

  MQ7.calibrate();
}

void sendBT(char *d)
{
  Serial.print("<< BT ");
  Serial.println(d);
  pReadings->setValue(d);
}

void loop()
{
  char pkg[128];

  MQ7.package(co7Pkg);
  MICS6814.package(coPkg, nh3Pkg, no2Pkg);

  MQ135.package(mq135Pkg);

  sprintf(pkg, "%s %s %s %s %s", co7Pkg, coPkg, nh3Pkg, no2Pkg, mq135Pkg);
  sendBT(pkg);

  delay(500);
}
