#include <Wire.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define SLAVE_ADDR 0x28

char received[32];
int indexPos = 0;

void receiveEvent(int howMany)
{
  indexPos = 0;

  while (Wire.available())
  {
    char c = Wire.read();
    received[indexPos++] = c;
  }

  received[indexPos] = '\0';

  Serial.print("Received: ");
  Serial.println(received);
}

void setup()
{
  Serial.begin(115200);

  Wire.begin(SLAVE_ADDR, SDA_PIN, SCL_PIN); // now pins clearly defined
  Wire.onReceive(receiveEvent);

  Serial.println("ESP32 I2C Slave Ready");
}

void loop()
{
}
