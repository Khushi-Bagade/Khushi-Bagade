#include<Servo.h>

Servo esc1;
Servo esc2;

int escpin1= 9;
int escpin2= 10;
int speed = 1000;

void setup() {
  Serial.begin(9600);
  esc1.attach(escpin1,1000,2000);
  esc2.attach(escpin2,1000,2000);
  esc1.writeMicroseconds(1000); 
  esc2.writeMicroseconds(1000);
  esc1.writeMicroseconds(speed);
  esc2.writeMicroseconds(speed);
}

void loop() {
  if(Serial.available()>1){
    int speed=Serial.parseInt();
    if(speed>=1000&&speed<=2000){
      Serial.print("IN LOop" ) ;
      Serial.print(speed);
    } 
  esc1.writeMicroseconds(speed);
  esc2.writeMicroseconds(speed);
  Serial.print("\t") ;
  Serial.println(speed);
  }
}
