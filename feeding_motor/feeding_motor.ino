#define hall A0
#define pwm 19
#define ENC_COUNT_REV 56
volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
void updateEncoder2();

void setup() {
 pinMode(pwm,OUTPUT);
 pinMode(hall,INPUT);
 pinMode(13, INPUT_PULLUP);
 pinMode(12, INPUT);
 attachInterrupt(digitalPinToInterrupt(34), updateEncoder1, RISING);
 attachInterrupt(digitalPinToInterrupt(35), updateEncoder2, RISING);
 Serial.begin(115200);

}

void loop() {
  int hall_val = digitalRead(12);
  Serial.println(hall_val);
  // Serial.print(encoderValue1) ;
  // Serial.print("\t") ;
  // Serial.println(encoderValue2) ;
  // analogWrite(pwm,0) ;
  // digitalWrite( rly , HIGH ) ;
  // delay(2000) ;
  // digitalWrite( rly , LOW ) ;
  // delay(2000) ;
  // Serial.println("0");
  analogWrite(pwm,30) ;
  // digitalWrite( rly , HIGH ) ;
  // delay(2000) ;
  // digitalWrite( rly , LOW ) ;
  // delay(2000) ;
  // Serial.println("50");
  // analogWrite(pwm,100) ;
  // digitalWrite( rly , HIGH ) ;
  // delay(2000) ;
  // digitalWrite( rly , LOW ) ;
  // delay(2000) ;
  // Serial.println("100");
  // analogWrite(pwm,150) ;
  // digitalWrite( rly , HIGH ) ;
  // delay(2000) ;
  // digitalWrite( rly , LOW ) ;
  // delay(2000) ;
  // Serial.println("150");
  // analogWrite(pwm,200) ;
  // digitalWrite( rly , HIGH ) ;
  // delay(2000) ;
  // digitalWrite( rly , LOW ) ;
  // delay(2000) ;
  // Serial.println("200");
  // analogWrite(pwm,255) ;
  // digitalWrite( rly , HIGH ) ;
  // delay(2000) ;
  // digitalWrite( rly , LOW ) ;
  // delay(2000) ;
  // Serial.println("255");
}
void updateEncoder1(){
  ++encoderValue1;
}

void updateEncoder2(){
  ++encoderValue2;
}