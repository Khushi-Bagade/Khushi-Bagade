-
int j=5; 
int p=7;
int b ;

void setup() {
  pinMode(p , OUTPUT);
  pinMode(j , OUTPUT);
  Serial.begin(115200);
  digitalWrite(j, HIGH);
  digitalWrite(p, HIGH); 
}

void loop() {
  b = Serial.parseInt() ;
  if (b == 1){
    digitalWrite(j, LOW); 
    delay(25); 
    digitalWrite(p, LOW);  
    delay(150);
    digitalWrite(p, HIGH);
    delay(400); 
    digitalWrite(j, HIGH);
    delay(600); 
  }else if (b == 2){
    digitalWrite(j, LOW); 
  }else if (b == 3){
    digitalWrite(j, HIGH);
  }else if (b == 4){
    digitalWrite(p, LOW); 
  }else if (b == 5){
    digitalWrite(p, HIGH);
  }
  Serial.println(b);
}