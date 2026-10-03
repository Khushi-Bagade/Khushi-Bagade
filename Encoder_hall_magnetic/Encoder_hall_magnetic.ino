#define channelA  2
#define channelB  4
int a = 7;
int stopped;

int targetrevolution = 100;
int count = 0; 
int lastTime = 0;

  int currentTime = millis();
  int time ;
  int RPM,RPS;

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2),Interrupt,HIGH);


  int digitalRead(7,HIGH);

 }
void loop(){
 currentTime = millis();
  if(currentTime - lastTime >= 1000){
  lastTime = currentTime ;

 }
  RPS=((count/56));
  RPM = RPS*60;

  Serial.println(count); 
  Serial.println(time);
  Serial.println(RPS);
  Serial.println(RPM);

  if(count>= targetrevolution*60){
    stop ();
  }

  }

void Interrupt() {
  count++;
}

void stop(){
  int digitalRead(7,LOW);
    Serial.println(stopped);

}
