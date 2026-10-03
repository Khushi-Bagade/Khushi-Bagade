#define button 2
#define relay 3

int buttonstate = 0;


void setup() {
  pinMode(relay,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  // put your setup code here, to run once:

}

void loop() {
buttonstate = digitalRead(button);

if(buttonstate = HIGH){
  digitalWrite(relay,HIGH);

}
   else{
   digitalWrite(relay,LOW);
   }

}
