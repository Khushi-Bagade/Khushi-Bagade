#include <Wire.h> 
#include "CytronMotorDriver.h"
#include <PS4BT.h>
#include <usbhub.h>


#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;

BTD Btd(&Usb); 

PS4BT PS4(&Btd, PAIR);

int hd;
int a,b,c;
int merge = 0;
int kp = 1;
int ki = 1;
int kd = 1;

int previousError = 0;

int error = 0;
int interror = 0;
int dererror = 0;
int output=0;

// #define motor1
// #define motor2
// #define motor3
// #define motor4
int val = 50; // Speed for motors
int value;
CytronMD motor1(PWM_DIR, 3, 2);
CytronMD motor2(PWM_DIR, 5, 4);
CytronMD motor3(PWM_DIR, 6, 7);
CytronMD motor4(PWM_DIR, 8, 9);



// Motor control functions - now properly declared globally
void forward(int val);
void backward(int val);
void right(int val);
void left(int val);
void stop(int val);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void setup() {
  Serial.begin(9600);          
  Wire.begin(7); 
  Wire.onReceive(onReceiveEvent); 
  Serial.begin(115200);
#if !defined(MIPSEL)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void loop() 
{




 Usb.Task();
  if (PS4.getButtonClick(PS)) {
    Serial.print(F("\r\nPS"));
    PS4.disconnect();
  }

  

  else {
    if(PS4.getButtonClick(L1)&&val<255) {
      val=+5;
      Serial.print(F("\r\nL1"));  //increase
    }
    else if(PS4.getButtonClick(R1)&&val>0){
      val=-5;
      Serial.print(F("\r\nR1"));      //decrease
    }
    if (PS4.getButtonPress(UP)) {
      Serial.print(F("\r\nUp"));
      forward(val);
    }
    else if (PS4.getButtonPress(RIGHT)) {
      Serial.print(F("\r\nRight"));
     right(val);
    } 
    else if (PS4.getButtonPress(DOWN)) {
      Serial.print(F("\r\nDown"));
      backward(val);
    } 
    else if (PS4.getButtonPress(LEFT)) {
      Serial.print(F("\r\nLeft"));
      left(val);
    }
    
    else{
      
      stop(val);
      
    }
  }  
}
  void forward(int val) {
  motor1.setSpeed(-val);
  motor2.setSpeed(-val);
  motor3.setSpeed(val);
  motor4.setSpeed(val);
}

  void backward(int val)
  {
  motor1.setSpeed(val);
  motor2.setSpeed(val);
  motor3.setSpeed(-val);
  motor4.setSpeed(-val);
}

  void left(int val) 
  {
  motor1.setSpeed(val);
  motor2.setSpeed(-val);
  motor3.setSpeed(val);
  motor4.setSpeed(-val);
}

  void right(int val)
   {
  motor1.setSpeed(-val);
  motor2.setSpeed(val);
  motor3.setSpeed(-val);
  motor4.setSpeed(val);
}
  void stop(int val)
  {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}



void onReceiveEvent (int a , int b ,int c ){
a=Wire.read();
b=Wire.read();
c=Wire.read();
merge = (a*100) + (b*10) + c;
Serial.print("merge: ");
Serial.println(merge);
Serial.print("a: ");
Serial.println(a);
Serial.print("b: ");
Serial.println(b);
Serial.print("c: ");
Serial.println(c);
}


int PID( int setpoint, int currentValue){

  error = setpoint - currentValue ;
  interror = previousError + error ; 
  dererror= previousError - error ;
  output = kp*error + ki*interror + kd*dererror;

  Serial.print("output: ");
  Serial.println(output);

  previousError = error;

  return(output);
}
