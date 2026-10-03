#include "CytronMotorDriver.h"


CytronMD motor(PWM_DIR,3,4);


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  motor.setSpeed(200);
  delay(1000);
  motor.setSpeed(200);
  delay(1000);

  // put your main code here, to run repeatedly:

}