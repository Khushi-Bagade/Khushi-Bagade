#define ledpin 2
int pwm ;
void setup() {
  pinMode(ledpin , OUTPUT);

}

void loop() {
  for (pwm = 0;pwm<=255;pwm++){
    analogWrite(ledpin , pwm);
   delay(100); 
  }
  for (pwm = 255;pwm>=0;pwm--){
    analogWrite(ledpin , pwm);
    delay(100);
  }
}
  // put your main code here, to run repgb6eatedly:


