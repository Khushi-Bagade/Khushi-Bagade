#include<HardwareSerial.h>
#define rx  //15
#define tx   // 1



HardwareSerial espSerial(1);

void setup() {
  espSerial.begin(115200 , 15 , 16);

}

void loop() {
  espSerial.println("hello");

}
