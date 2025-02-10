#include<HardwareSerial.h>
#define rx
#define tx



HardwareSerial espSerial(0);

void setup() {
  espSerial.begin(115200);

}

void loop() {
  espSerial.println("hello");

}
