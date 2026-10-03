#include <ps5Controller.h>
#include "Arduino_NineAxesMotion.h" 
#include <Wire.h>
#include "ESP_Motor_Driver.h"

NineAxesMotion mySensor;

TaskHandle_t Task1;
TaskHandle_t Task2;

CytronMD motor2(PWM_DIR, 14, 27, 0, 10000, 8);
CytronMD motor1(PWM_DIR, 13, 12, 1, 10000, 8);
CytronMD motor3(PWM_DIR, 26, 25, 2, 10000, 8);
CytronMD motor4(PWM_DIR, 33, 32, 3, 10000, 8);

unsigned long lastStreamTime = 0;       
const int streamPeriod = 20;

int a ;  
int setpoint = 40; 
int new_o;     
int k;
int val;
int lastVal = -1; 
bool o_val = false;
int c_val = 50;
int p = 50;
int m = 50;
int R1 = 0;
int L1;

int ki = 0;
int kp = 2;
int kd = 0;

int error;
int pre_E = 0;
int pro_E ;
int inte_E;
int der_E;
int currentval;
int output;

void forward();
void backward();
void right();
void left();
void L2();
void R2();
void stop();
 
void setup() {  
  Serial.begin(115200);
  // ps5.begin("D0:BC:C1:A3:40:83");
   ps5.begin("7c:66:ef:3c:ef:d5");
  Wire.begin();       
  xTaskCreatePinnedToCore(Task1Code, "Task1", 10000, NULL, 1, &Task1, 1);           
  // xTaskCreatePinnedToCore(Task2Code, "Task2", 10000, NULL, 1, &Task2, 0);           
  mySensor.initSensor();
  mySensor.setOperationMode(OPERATION_MODE_NDOF);   
  mySensor.setUpdateMode(MANUAL);	
}

void Task1Code(void * parameters) {
  while(1){
    if(ps5.isConnected()){
      if(ps5.PSButton()){
          Serial.println("esp reset");
          ESP.restart();
        }
      if(ps5.Right()){
        Serial.println("Right Button");
        right();
      } 
      else if(ps5.Down()){
        Serial.println("Down Button");
        backward();
      } 
      else if(ps5.Up()){
        Serial.println("Up Button");
        forward();  
      }
      else if(ps5.Left()){
        Serial.println("Left Button");
        left();
      }
      // else if(ps5.L2()){
      //   Serial.println("L2 Button");
      //   L2();
      //   setpoint = a ;
      //   Serial.print("Setpoint updated to: ");
      //   Serial.println(setpoint);
      // }
      // else if(ps5.R2()){
      //   Serial.println("R2 Button");
      //   R2();
      //   setpoint = a ;
      //   Serial.print("Setpoint updated to: ");
      //   Serial.println(setpoint);
      // }   
      else{
        stop();
      }
    
      if (ps5.R1() == 1 && c_val >50 && c_val <= 255 && R1 == 0 ) {
        c_val -= 5;  
        R1=1;   
        Serial.println(val); 
      } 
      else if (ps5.L1() == 1 &&  c_val >= 0 && c_val < 255 && L1 == 0) {
        c_val += 5; 
        L1=1; 
        Serial.println(val);
      }
      else if(ps5.R1() == 0 && ps5.L1() == 0){
        R1 = 0;
        L1 = 0; 
      }
    }  
  output = pid (ki , kp ,  kd , setpoint , error, currentval);
  p = constrain(val + output, -255 , 255);
  m = constrain(val - output, -255 , 255);
  }
}

// void Task2Code(void * parameters){
//   while(1){
//     while (millis() - lastStreamTime >= streamPeriod)
//     {
//     lastStreamTime = millis();
//     mySensor.updateEuler();        
//     mySensor.updateCalibStatus(); 
//     k = mySensor.readEulerHeading();
//     Serial.print("a:");
//     Serial.print(a);
//     Serial.print("\t");
//     Serial.print("new_o: ");
//     Serial.print(new_o);
//     Serial.println("\n");
//     if (Serial.available()) {
//       val = Serial.parseInt(); 
       
    
//       if (val > 0 && val <= 9 && val != lastVal) {
//         lastVal = val; 
//         o_val = true;
//          a=k;   
//         if (k > 0 && k <= 180) {
//          Serial.println(k);
//         } 
//         else if (k >= 180) {
//           k = k - 360;
//           Serial.println(k); 
//             a=k; 
//         }

//         int diff = setpoint - k;
//          if(diff != 180){
//           if(diff < 180){
//            new_o = setpoint + 180;
//             if(diff > 180){
//              new_o -=360;
//              }
//             }
//           }
//         }
//       } 
//     }      
//   }
// }

void loop(){
}

int pid(int ki, int kp, int kd, int setpoint, int error, int currentval) {
  error = setpoint - currentval;
  inte_E += error;  
  der_E = error - pre_E; 
  output = (kp * error) + (ki * inte_E) + (kd * der_E);
  pre_E = error; 
  // Serial.print("PID Output: ");
  // Serial.println(output);
  return (output);
}

void backward(){
  motor1.setSpeed(m);
  motor2.setSpeed(m);
  motor3.setSpeed(p);
  motor4.setSpeed(p);
}

void forward   () {
  motor1.setSpeed(p);
  motor2.setSpeed(p);
  motor3.setSpeed(m);
  motor4.setSpeed(m);
}

void left() {
  motor1.setSpeed(p);
  motor2.setSpeed(m);
  motor3.setSpeed(p);
  motor4.setSpeed(m);
}

void right() {
  motor1.setSpeed(m);
  motor2.setSpeed(p);
  motor3.setSpeed(m);
  motor4.setSpeed(p);
}

void L2() {
  motor1.setSpeed(m);
  motor2.setSpeed(p);
  motor3.setSpeed(m);
  motor4.setSpeed(p);
}

void R2() {
  motor1.setSpeed(m);
  motor2.setSpeed(p);
  motor3.setSpeed(m);
  motor4.setSpeed(p);
}
 
void stop() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

