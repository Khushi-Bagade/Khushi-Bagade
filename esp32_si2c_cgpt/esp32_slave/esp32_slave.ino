#include <Wire.h>

#define I2C_ADDRESS 9  

void setup() {
  Serial.begin(115200);
  

  Wire.begin(I2C_ADDRESS); 
  
 
  Wire.onReceive(receiveData); 
  
  Serial.println("Slave ready to receive data");
}

void loop() {

}

void receiveData(int byteCount) {
  while (Wire.available()) {
    char c = Wire.read();  
    Serial.print(c); 
  }
  Serial.println();

}