 #include<Servo.h>

 Servo myServo;

  int kp=1;
  int ki=1;
  int kd=1;

  int proerror;
  int interror;
  int dererror;

  int previousError = 0;
  int setpoint = 20;
  int output = 0;
  int error = 0;
  
  const int trigPin = 9;
  const int echoPin = 10;
  const int motorPin = 6;

  long duration;
  int distance;
  int pos;
  
  void setup() { 
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    myServo.attach(9);
}

void loop() { 
   
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  // Short delay to ensure a clean signal
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); // Pulse width of 10 microseconds
  digitalWrite(trigPin, LOW); 

  duration = pulseIn(echoPin, HIGH);

   distance = duration * 0.0344 / 2;
   output = PID(setpoint, distance);
   output = constrain(output, 0, 180);
   myServo.write(output);


  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("OUTPUT: ");
  Serial.println(output);
 
}
  
  
int PID( int setpoint, int currentValue){
  error = setpoint - currentValue ;
  interror+=error ; 
  dererror= previousError - error ;
  output = kp*error + ki*interror + kd*dererror;
  
  previousError = error;

  return(output);
}