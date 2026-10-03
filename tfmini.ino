#include <SoftwareSerial.h>
SoftwareSerial tfminiSerial(11, 10);

void setup() {
  
  Serial.begin(115200);
  tfminiSerial.begin(115200);
  // Serial.println("TFMini Plus - Simple Example");

}
void loop() {
  
  if (tfminiSerial.available() >= 9) {
    
    byte frame[9];
    for (int i = 0; i < 9; i++) {
      frame[i] = tfminiSerial.read();
    }
    
    if (frame[0] == 0x59 && frame[1] == 0x59) {
      uint16_t distance = (frame[3] << 8) | frame[2]; 
      uint16_t strength = (frame[5] << 8) | frame[4];  

      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" cm, Strength: ");
      Serial.println(strength);
    }
  }
delay(100);
}
