#include "BluetoothSerial.h"
#include "Sensor.h"

BluetoothSerial SerialBT;

// identifier, resistance, port
Sensor MQ7("CO", 2000, 4);

void setup()
{
  Serial.begin(9600);
  Serial.println("DEVICE START");
  
  SerialBT.begin("Carsu");
  Serial.println("BLUETOOTH OK");
  
  MQ7.calibrate();
}

void sendBT(String d)
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
  sendBT(MQ7.package());
  
  recvBT();
  delay(500);
}
