#include <Wire.h>

#define I2C_ADDRESS 9 

void setup() {
  Serial.begin(115200);
  

  Wire.begin(); 
  
  delay(1000);  
}

void loop() {
  Wire.beginTransmission(I2C_ADDRESS); 
  Wire.write("Hello from ESP32 Master!"); 
  Wire.endTransmission(); 
  
  Serial.println("Data sent to Slave");
  
  delay(1000);  
}

