#include <CytronMotorDriver.h>
#include <ps5Controller.h>
#include <Wire.h>
#include <ESP32Servo.h>

#define rly 19
#define bldc1 2
#define bldc2 4

Servo SL_Servo;
Servo SR_Servo;

TaskHandle_t Task1;
TaskHandle_t Task2;

CytronMD motor1(PWM_DIR, 14, 27);
CytronMD motor2(PWM_DIR, 13, 12);
CytronMD motor3(PWM_DIR, 26, 25);
CytronMD motor4(PWM_DIR, 33, 32);

int c_val = 50;
int R1;
int L1;

int curr_tri , pre_tri , curr_cir , pre_cir ;
int bldc_spd = 1000;


void forward();
void backward();
void right();
void left();
void L2();
void R2();
void stop();
void Orientation(void*);

void setup() { 
  Serial.begin(115200);
  Wire.begin();
  // ps5.begin("D0:BC:C1:A3:40:83");
  ps5.begin("7c:66:ef:3c:ef:d5");
  xTaskCreatePinnedToCore(Maincode, "Task1", 10000, NULL, 1, &Task1, 1);
  xTaskCreatePinnedToCore(Orientation, "Task2", 10000, NULL, 1, &Task2, 0);
  ESP32PWM::allocateTimer(3) ;
  SL_Servo.setPeriodHertz(50);
  SR_Servo.setPeriodHertz(50);
  SL_Servo.attach(2, 1000, 2000) ; 
  SR_Servo.attach(4, 1000, 2000) ; 
  SL_Servo.writeMicroseconds(1000) ;
  SR_Servo.writeMicroseconds(1000) ; 
  delay(300) ;

  pinMode(rly , OUTPUT);
  digitalWrite(rly, HIGH);

}

void Maincode(void * parameters) {
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
      else if(ps5.L2()){
        Serial.println("L2 Button");
        L2();
        }
      else if(ps5.R2()){
        Serial.println("R2 Button");
        R2();
        }
      else{
        stop();
        }

      curr_tri = ps5.Triangle();
      curr_cir = ps5.Circle();

      if (curr_tri == 1 && pre_tri == 0) {
        bldc_spd += 5;
        Serial.println("bldc_spd");
        if (bldc_spd > 2000) bldc_spd = 2000;
      } else if (curr_cir == 1 && pre_cir == 0) {
        bldc_spd -= 5;
        Serial.println("bldc_spd");
        if (bldc_spd < 1000) bldc_spd = 1000;
      }

      pre_tri = curr_tri;
      pre_cir = curr_cir;

      SL_Servo.writeMicroseconds(bldc_spd);
      SR_Servo.writeMicroseconds(bldc_spd);

      if (ps5.R1() == 1 && c_val >= 5 && R1 == 0) {
        c_val -= 5;  
        R1 = 1;   
        Serial.println(c_val); 
      } 
      else if (ps5.L1() == 1 && c_val <= 250 && L1 == 0) {
      c_val += 5; 
      L1 = 1; 
      Serial.println(c_val);
      } 
      else if (ps5.R1() == 0 && ps5.L1() == 0) {
      R1 = 0;
      L1 = 0; 
      }
      
    }
  }
}

void loop() {
}

void Orientation(void*parameters){

}
void backward(){
  motor1.setSpeed(c_val);
  motor2.setSpeed(c_val);
  motor3.setSpeed(c_val);
  motor4.setSpeed(c_val);
}

void forward () {
  motor1.setSpeed(c_val);
  motor2.setSpeed(c_val);
  motor3.setSpeed(c_val);
  motor4.setSpeed(c_val);
}

void left() {
  motor1.setSpeed(c_val);
  motor2.setSpeed(c_val);
  motor3.setSpeed(c_val);
  motor4.setSpeed(c_val);
}

void right() {
  motor1.setSpeed(c_val);
  motor2.setSpeed(c_val);
  motor3.setSpeed(c_val);
  motor4.setSpeed(c_val);
}
void L2() {
  motor1.setSpeed(c_val);
  motor2.setSpeed(c_val);
  motor3.setSpeed(c_val);
  motor4.setSpeed(c_val);
}

void R2() {
  motor1.setSpeed(c_val);
  motor2.setSpeed(c_val);
  motor3.setSpeed(c_val);
  motor4.setSpeed(c_val);
}
void stop() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}
 