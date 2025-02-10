#include<Wire.h>

// #define I2C_DEV_ADDR 0x55

#define gpio22
#define gpio21
 int data;
 int i=0;

 void setup() {
  Wire.begin(0x55);
  Serial.setDebugOutput(true);
  Wire.onReceive(DataReceive);
}
 void onRequest() {
  Wire.print(i++);
  Wire.print(" Packets.");
  Serial.println("onRequest");
}
 void loop(){ 
}
 void DataReceive(int howmany)
 {
  while(Wire.available()){
  data = Wire.read();
  Serial.write(data);
}
}
  
  
// ____________________________________________________________________________________
// __________________________________________________________________________________


// include "Wire.h"

// #define I2C_DEV_ADDR 0x55

// uint32_t i = 0;

// void onRequest() {
//   Wire.print(i++);
//   Wire.print(" Packets.");
//   Serial.println("onRequest");
// }

// void onReceive(int len) {
//   Serial.printf("onReceive[%d]: ", len);
//   while (Wire.available()) {
//     Serial.write(Wire.read());
//   }
//   Serial.println();
// }

// void setup() {
//   Serial.begin(115200);
//   Serial.setDebugOutput(true);
//   Wire.onReceive(onReceive);
//   Wire.onRequest(onRequest);
//   Wire.begin((uint8_t)I2C_DEV_ADDR);

// #if CONFIG_IDF_TARGET_ESP32
//   char message[64];
//   snprintf(message, 64, "%lu Packets.", i++);
//   Wire.slaveWrite((uint8_t *)message, strlen(message));
// #endif
// }

// void loop() {}

#if CONFIG_IDF_TARGET_ESP32
  char message[64];
  snprintf(message, 64, "%lu Packets.", i++);
  Wire.slaveWrite((uint8_t *)message, strlen(message));
#endif