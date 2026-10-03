  int BUTTON_PIN = 7;
  int LED_PIN = 3;
  int Counter;

  int ledstate = 0;
  int lastbuttonstate ;
  int currentbuttonstate ;

 void setup() {
  Serial.begin(9600);
  pinMode( BUTTON_PIN,INPUT);
  pinMode( LED_PIN,OUTPUT );
  currentbuttonstate = digitalRead(BUTTON_PIN);
  
 }

 void loop() {
  lastbuttonstate == LOW && currentbuttonstate == HIGH;
  currentbuttonstate = digitalRead(BUTTON_PIN);

  if(lastbuttonstate == HIGH )  {
    Serial.println("the button is pressed: ");
    if(ledstate == LOW ){
      ledstate = HIGH;
      Counter++ ;
      Serial.println("LED IS HIGH");

    }
  else {
  ledstate == LOW ;
  Serial.println("led is off"); 
 }
  }
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN,ledstate);
}
