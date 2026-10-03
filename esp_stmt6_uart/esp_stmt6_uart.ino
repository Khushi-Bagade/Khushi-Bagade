#define RXD2 16
#define TXD2 17

String data = "";

void setup()
{
  Serial.begin(115200);          // PC monitor
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.println("ESP32 Ready");
}

void loop()
{
  while (Serial2.available())
  {
    char c = Serial2.read();

    if (c == '\n')
    {
      Serial.print("Received: ");
      Serial.println(data);
      data = "";
    }
    else if (c != '\r')
    {
      data += c;
    }
  }
}
