#include "BluetoothSerial.h"
#include "Carsu.h"

BluetoothSerial SerialBT;

void setup()
{
  Serial.begin(9600);
  Serial.println("DEVICE START");
  SerialBT.begin("Carsu");
  Serial.println("BLUETOOTH OK");
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
  float ppmCO = 1.23;
  float ppmCO2 = 12.34;

  sendBT(Carsu::package("CO", ppmCO));
  sendBT(Carsu::package("CO2", ppmCO2));

  recvBT();

  delay(500);
}
