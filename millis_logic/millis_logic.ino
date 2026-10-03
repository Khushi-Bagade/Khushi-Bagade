unsigned long delayTime;          
unsigned long pre_v = 0; 
unsigned long cur_v;      

void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);

}

void loop() {
  cur_v = millis();    
 
  if (cur_v - pre_v >= delayTime) {
    pre_v = cur_v; 
    digitalWrite(2,HIGH);
  }
  else{    
    digitalWrite(2,LOW);
  }
    delayTime += 100;
    // Serial.println(delayTime);
}

