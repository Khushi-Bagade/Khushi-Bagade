#include <ESP32Servo.h>
#include <ps5Controller.h>

#define pin1 2
#define pin2 4

int Cstate ;
int Pstate;
int a;
int speed = 1000;
Servo esc1, esc2;
bool Square = false;
bool Triangle= false;

void setup() {
  Serial.begin(115200);
  // ps5.begin("D0:BC:C1:A3:40:83");
  ps5.begin("7c:66:ef:3c:ef:d5");
  esc1.attach(pin1, 1000, 2000);
  esc2.attach(pin2, 1000, 2000);
}

void loop() {
  if (ps5.isConnected()) {

    Cstate = ps5.Options();
    if(Cstate != Pstate){
      if(Cstate == 1){
        a++;
      }
    }
    Pstate = Cstate;
    
    if(a%2==1){
      if(ps5.Square() == 1 && ps5.Square() == 0){
      speed -=5;
      Square = 1;
      }
      if(ps5.Triangle() == 1 && speed < 2000 && Triangle == 0){
        speed +=5;
        Triangle = 1;
      }
      else if(ps5.Square() ==0 && ps5.Triangle() == 0){
        Square = 0;
        Triangle = 0;
      }
   
      esc1.writeMicroseconds(speed);
      esc2.writeMicroseconds(speed);
    }
    else {
      esc1.writeMicroseconds(1000);
      esc2.writeMicroseconds(1000);
    }
    Serial.print("a: ");
    Serial.print(a);
    Serial.print("Speed: ");
    Serial.println(speed);
  }
}




// #include <ESP32Servo.h>
// #include <ps5Controller.h>


// #define bldc1 2
// #define bldc2 4

// Servo SL_Servo ;
// Servo SR_Servo ;
// int curr_tri , curr_cir , pre_tri , pre_cir;
// int bldc_spd = 1000;


// void setup() {
//   Serial.begin(9600);
//    ps5.begin("D0:BC:C1:A3:40:83");
//   ESP32PWM::allocateTimer(3) ;
//   SL_Servo.setPeriodHertz(50);
//   SR_Servo.setPeriodHertz(50);
//   SL_Servo.attach(2, 1000, 2000) ; 
//   SR_Servo.attach(4, 1000, 2000) ; 
//   SL_Servo.writeMicroseconds(1000) ;
//   SR_Servo.writeMicroseconds(1000) ; 
//   // put your setup code here, to run once:

// }

// void loop() {

//   if(ps5.isConnected()){
//     Serial.println("connected");

//     curr_tri = ps5.Triangle() ;
//     curr_cir = ps5.Circle() ;
//     if     (curr_tri == 1 && pre_tri == 0) bldc_spd += 5 ;
//     else if(curr_cir == 1 && pre_cir == 0) bldc_spd -= 5 ;
//     pre_tri = curr_tri ;
//     pre_cir = curr_cir ;
//     SL_Servo.writeMicroseconds(bldc_spd) ;
//     SR_Servo.writeMicroseconds(bldc_spd) ; 
//   }
//   else{
//         SL_Servo.writeMicroseconds(1000) ;
//     SR_Servo.writeMicroseconds(1000) ; 
//   }
//   // put your main code here, to run repeatedly:

// }