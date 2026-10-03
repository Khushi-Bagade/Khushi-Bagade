#include "CytronMotorDriver.h"

int a , spd ;
// Configure the motor driver.
CytronMD motor1(PWM_DIR, 3, 4);  // PWM = Pin 3, DIR = Pin 4.
CytronMD motor2(PWM_DIR, 9 , 10);

// The setup routine runs once when you press reset.
void setup() {
  Serial.begin(115200) ;
}


// The loop routine runs over and over again forever.
void loop() {
  a = Serial.parseInt();
  if(Serial.available() && a>= -255 && a <= 255){
    spd = a ;
  }
  motor1.setSpeed(spd);
  motor2.setSpeed(spd);
  Serial.print(a) ;
  Serial.print("\t") ;
  Serial.print(spd) ;
  Serial.print("\n");
}