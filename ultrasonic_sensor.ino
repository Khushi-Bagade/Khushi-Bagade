// Define the pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Variable to store the duration and distance
long duration;
int distance;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  
  // Set the trigPin as an OUTPUT and echoPin as an INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Send a 10us pulse to the trigger pin to start the measurement
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  // Short delay to ensure a clean signal
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); // Pulse width of 10 microseconds
  digitalWrite(trigPin, LOW); 

  // Read the pulse duration from the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the duration
  // Sound travels at 343 meters per second, so we use the formula:
  // distance = (duration / 2) * (speed of sound)
  // speed of sound = 34300 cm/s (in air at room temperature)
  distance = duration * 0.0344 / 2;

  // Output the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait before taking another reading
  delay(500);
}
