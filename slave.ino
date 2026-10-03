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
   int ki = 0;
   int kd = 0;
   int p;
 int previousError = 0;
 int k;

  int error = 0;
  int interror = 0;
  int dererror = 0;
  int output=0;
  int setpoint = 0;

int val = 50; // Speed for motors
int value;
CytronMD motor1(PWM_DIR, 3, 2);
CytronMD motor2(PWM_DIR, 5, 4);
CytronMD motor3(PWM_DIR, 7, 6);
CytronMD motor4(PWM_DIR, 9, 8);



// Motor control functions - now properly declared globally
void forward(int val);
void backward(int val);
void right(int val);
void left(int val);
void stop(int val);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void setup() {         
  Wire.begin(7); 
  Wire.onReceive(onReceiveEvent); 
  Serial.begin(115200);
  #if !defined(_MIPSEL_)
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
    
    if(merge>180){
      k=merge-360;
      
    }
    else{
      k=merge;
    }
    Serial.print(k);
    Serial.print("  ");
    int x = constrain(val + output,0,200);
    int y = constrain(val - output,0,200);
    Serial.print("x,y: ");
    Serial.print(x);
    Serial.print("  ");
    Serial.println(y);
    



    if(PS4.getButtonClick(L1)&&val<255) {
      val=+5;
      // Serial.print(F("\r\nL1"));  //increase
    }
    else if(PS4.getButtonClick(R1)&&val>0){
      val=-5;
      // Serial.print(F("\r\nR1"));      //decrease
    }
    p=PID(setpoint , k);
    // Serial.print("p: ");
    // Serial.println(p);

    
    if (PS4.getButtonPress(UP)) {
      // Serial.print(F("\r\nUp"));
      forward(x,y);
    }
    else if (PS4.getButtonPress(RIGHT)) {
      // Serial.print(F("\r\nRight"));
     right(x,y);
    } 
    else if (PS4.getButtonPress(DOWN)) {
      // Serial.print(F("\r\nDown"));
      backward(x,y);
    } 
    else if (PS4.getButtonPress(LEFT)) {
      // Serial.print(F("\r\nLeft"));
      left(x,y);
    }
    
    else{
      
      stop();
      
    }
  }  
}
  void forward(int x, int y) {
  motor1.setSpeed(-x);
  motor2.setSpeed(-x);
  motor3.setSpeed(y);
  motor4.setSpeed(y);
}

  void backward(int x , int y)
  {
  motor1.setSpeed(y);
  motor2.setSpeed(y);
  motor3.setSpeed(-x);
  motor4.setSpeed(-x);
}

  void left(int x,int y) 
  {
  motor1.setSpeed(x);
  motor2.setSpeed(-y);
  motor3.setSpeed(x);
  motor4.setSpeed(-y);
}

  void right(int x, int y)
   {
  motor1.setSpeed(-y);
  motor2.setSpeed(x);
  motor3.setSpeed(-y);
  motor4.setSpeed(x);
}
  void stop()
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
//  Serial.print("merge: ");
//  Serial.println(merge);
//  Serial.print("a: ");
//  Serial.println(a);
//  Serial.print("b: ");
//  Serial.println(b);
//  Serial.print("c: ");
//  Serial.println(c);
}


int PID( int setpoint, int currentValue){

  error = setpoint - currentValue ;
  interror = previousError + error ; 
  dererror= previousError - error ;
  output = kp*error + ki*interror + kd*dererror;

  // Serial.print("output: ");
  // Serial.println(output);

  previousError = error;

  return(output);
}