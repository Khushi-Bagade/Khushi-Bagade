#include<HardwareSerial.h>
HardwareSerial espSerial(0);

void setup() {
 Serial.begin(9600);
 espSerial.begin(115200);

}

void loop() {
  if(espSerial.available()>0){
  String Mod = espSerial.readStringUntil('\n');
  Mod.trim();
  Serial.println(Mod);
 

}
}