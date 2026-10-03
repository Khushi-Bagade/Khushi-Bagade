#include "ESP_Motor_Driver.h"
#include <ps5Controller.h>
#include "Arduino_NineAxesMotion.h" 
#include <Wire.h>
#include <ESP32Servo.h>
#include "HardwareSerial.h"

TaskHandle_t Task1;
TaskHandle_t Task2;

// #define rly 14

#define rly 19
#define bldc1 2
#define bldc2 4

Servo SL_Servo;
Servo SR_Servo;

CytronMD motor1(PWM_DIR, 14, 27, 0, 5000, 8);
CytronMD motor2(PWM_DIR, 13, 12, 1, 5000, 8);
CytronMD motor3(PWM_DIR, 26, 25, 2, 5000, 8);
CytronMD motor4(PWM_DIR, 32, 33, 3, 5000, 8);
NineAxesMotion mySensor;

HardwareSerial espSerial(0);

int c_val = 50;
int R1, L1;
int d_timer;
int a_timer;
unsigned long cur_s = 0;
unsigned long pre_s = 0;
int speed , target = 150;
bool increasing = true;

int k;
int setpoint;
int new_o;
int streamPeriod;
int lastStreamTime;

int Chassis_kp = 2;
int Chassis_ki = 0;
int Chassis_kd = 0;
int pre_err;
int p, m, pid_output;

int curr_shr, pre_shr, start;
int curr_Touch , pre_Touch;

int curr_tri , pre_tri , curr_cir , pre_cir , curr_cross , pre_cross;
int bldc_spd = 1060;

int forward();
int backward();
int right();
int left();
int L2();
int R2();
void stop();
void allstop(); //declare

enum MotionDirection {
  NONE,          //value 0
  FORWARD,       //value 1
  BACKWARD,      //value 2
  LEFT,          //value 3
  RIGHT,         //value 4
  ACLK,          //value 5
  CLK           //value 6
};

MotionDirection lastMotion = NONE;

void setup() {
  Serial.begin(115200);
  espSerial.begin(9600);
  // ps5.begin("7c:66:ef:3c:ef:d5");
  ps5.begin("D0:BC:C1:A3:40:83");
  Wire.begin();
  xTaskCreatePinnedToCore(Maincode, "Task1", 10000, NULL, 1, &Task1, 1);
  xTaskCreatePinnedToCore(Orientation, "Task2", 10000, NULL, 1, &Task2, 0);
  pinMode(19,OUTPUT) ;
  digitalWrite(19 , HIGH) ;
  mySensor.initSensor();
  mySensor.setOperationMode(OPERATION_MODE_NDOF);
  mySensor.setUpdateMode(MANUAL);
  ESP32PWM::allocateTimer(3) ;
  SL_Servo.setPeriodHertz(50);
  SR_Servo.setPeriodHertz(50);
  SL_Servo.attach(2, 1000, 2000) ; 
  SR_Servo.attach(4, 1000, 2000) ; 
  SL_Servo.writeMicroseconds(1000) ;
  SR_Servo.writeMicroseconds(1000) ; 
  delay(300) ;
}

void Maincode(void * parameters) {
  while (1) {
    if (ps5.isConnected()) {
      Serial.println("connected");

      if (ps5.PSButton()) {
        allstop();//functioin call
        ESP.restart();
      }
      else {
      curr_shr = ps5.Share();
      if (curr_shr != pre_shr && curr_shr > 0) ++start;
      pre_shr = curr_shr;

        if(start %2 == 1){
          Serial.print(start);
          Serial.print("\t");

          if (ps5.Right()) {
            right(speed, speed);
            lastMotion = RIGHT;
          } else if (ps5.Down()) {
            backward(speed, speed);
            lastMotion = BACKWARD;
          } else if (ps5.Up()) {
            forward(speed, speed);
            lastMotion = FORWARD;
          } else if (ps5.Left()) {
            left(speed, speed);
            lastMotion = LEFT;
          } else if (ps5.L2()) {
            setpoint = new_o;
            L2(map(ps5.L2Value() , 100 , 255 , 0 , 150));
            lastMotion = ACLK;
          } else if (ps5.R2()) {
            setpoint = new_o;
            R2(map(ps5.R2Value() , 100 , 255 , 0 , 150));
            lastMotion = CLK;
          } else {
            setpoint = new_o;
            stop(speed, speed);
          }

          pid_output = pid(Chassis_ki, Chassis_kp, Chassis_kd, 0, new_o);
          p = constrain(c_val + pid_output, -255, 255);
          m = constrain(c_val - pid_output, -255, 255);

          if (ps5.R1() == 1 && c_val >= 5 && R1 == 0) {
            c_val += 5;
            R1 = 1;
          } else if (ps5.L1() == 1 && c_val <= 255 && L1 == 0) {
            c_val -= 5;
            L1 = 1;
          } else if (ps5.R1() == 0 && ps5.L1() == 0) {
            R1 = 0;
            L1 = 0;
          }

          bool moving = ( ps5.L2() || ps5.R2() || ps5.Up() || ps5.Down() || ps5.Right() || ps5.Left());

          if (!moving) {
            speed = daccln(speed, 1, 0, d_timer);
            increasing = false;
            target = 0;
          } else if (moving && speed <= target) {
            target = c_val;
            speed = accln(speed, 1, target, a_timer);
            increasing = true;
          } else {
            speed = daccln(speed, 1 , target, d_timer);
            speed = target;
          }
        }
        else{
          stop() ;
        }
        curr_tri = ps5.Triangle();
        curr_cir = ps5.Circle();
        curr_cross = ps5.Cross();

        if (curr_tri == 1 && pre_tri == 0) {
        bldc_spd += 5;
        SL_Servo.writeMicroseconds(bldc_spd);
        SR_Servo.writeMicroseconds(bldc_spd);
        Serial.println("bldc_spd");
        if (bldc_spd > 2000) bldc_spd = 2000;
      } else if (curr_cir == 1 && pre_cir == 0) {
        bldc_spd -= 5;
        SL_Servo.writeMicroseconds(bldc_spd);
        SR_Servo.writeMicroseconds(bldc_spd);
        Serial.println("bldc_spd");
        if (bldc_spd < 1000) bldc_spd = 1000;
      }
      else if (curr_cross == 1 && pre_cross == 0){
        bldc_spd = 1000;
        SL_Servo.writeMicroseconds(bldc_spd);
        SR_Servo.writeMicroseconds(bldc_spd);
      }
      
      pre_tri = curr_tri;
      pre_cir = curr_cir;

      
     int y = ps5.RStickY();

     if(y>100){
      espSerial.println("c");
     }
     else if(y<-100){
      espSerial.println("C");
     } 
     else{
      espSerial.println("D");
     }

     curr_Touch = ps5.Touchpad();


     if(curr_Touch == 1){
       espSerial.println("A");
     }
     else {
       espSerial.println("a");
     }
     curr_Touch = pre_Touch;

      }
      Serial.println(speed);
      Serial.print("\t"); 
      Serial.println(c_val);  
      Serial.println(k);  
      Serial.print("\t");
      Serial.print(setpoint);
      Serial.print("\t"); 
      Serial.print(new_o);
      Serial.print("\t");
      // Serial.print(pid_output);
      // Serial.print("\n");
    } 
    // else {
    //   allstop();
    // }
  }
}

int accln(int av, int interval, int stpt, int a_timer) {
  cur_s = millis();
  if (cur_s - pre_s >= interval && av < stpt) {
    av += 1;
    pre_s = cur_s;
  }
  return av;
}

int daccln(int av, int interval, int stpt, int d_timer) {
  cur_s = millis();
  if (cur_s - pre_s >= interval && av > stpt) {
    av -= 1;
    pre_s = cur_s;
  }
  return av;
}

void loop() {}

void Orientation(void * parameters) {
  while (1) {
    if (millis() - lastStreamTime >= streamPeriod) {
      lastStreamTime = millis();
      mySensor.updateEuler();
      mySensor.updateCalibStatus();
      k = mySensor.readEulerHeading();

      if (k >= 180) k -= 360;
      if (k == 360) k = 0;

      if (k - setpoint > 180) {
        new_o = k - setpoint - 360;
      } else if (k - setpoint < -180) {
        new_o = k - setpoint + 360;
      } else {
        new_o = k - setpoint;
      }
    }
  }
}

int pid(int kp, int ki, int kd, int p_stpt, int currentval) {
  int error = currentval - p_stpt;
  int p_err = error;
  int int_err = error + pre_err;
  int der_err = error - pre_err;
  int output = (kp * p_err) + (ki * int_err) + (kd * der_err);
  pre_err = error;
  return output;
}

// function define
void backward(int a, int b) {
  motor1.setSpeed(-b);
  motor2.setSpeed(-b);
  motor3.setSpeed(a);
  motor4.setSpeed(a);
}

void forward(int a, int b) {
  motor1.setSpeed(a);
  motor2.setSpeed(a);
  motor3.setSpeed(-b);
  motor4.setSpeed(-b);
}

void right(int a, int b) {
  motor1.setSpeed(-b);
  motor2.setSpeed(a);
  motor3.setSpeed(-a);
  motor4.setSpeed(b);
}

void left(int a, int b) {
  motor1.setSpeed(a);
  motor2.setSpeed(-b);
  motor3.setSpeed(b);
  motor4.setSpeed(-a);
}

void L2(int speed) {             // aclk
 motor1.setSpeed(-speed);  
  motor2.setSpeed(-speed);   
  motor3.setSpeed(-speed);  
  motor4.setSpeed(-speed);
}

void R2(int speed) {                // clk
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
}

void stop(int a, int b) {
  switch (lastMotion) {
    case FORWARD:
      forward(a, b);
      break;
    case BACKWARD:
      backward(a, b);

      break;
    case LEFT:
      left(a, b);
      break;
    case RIGHT:
      right(a, b);
      break;
    // case ACLK:
    //   L2(a);
    //   break;
    // case CLK:
    //   R2(a);
    //   break;
    default:
      allstop();
      break;
  }
}
void stop(){
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);

}
void allstop() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
  SL_Servo.writeMicroseconds(1000);
  SR_Servo.writeMicroseconds(1000);
  
}

