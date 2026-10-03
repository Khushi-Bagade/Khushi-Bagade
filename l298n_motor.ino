int in1 =7;
int in2 =8;
int ena =5;
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(ena,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  delay(1000);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  delay(1000);
  // put your main code here, to run repeatedly:

}

