// Define the pin connected to the IR sensor's OUT pin
const int irSensorPin = 8;

// Variable to store the IR sensor state
int irSensorState = 0;

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Set the IR sensor pin as an input
  pinMode(irSensorPin, INPUT);
}

void loop() {
  // Read the state of the IR sensor
  irSensorState = digitalRead(irSensorPin);

  // If the sensor detects an object (LOW state)
  if (irSensorState == LOW) {
    Serial.println("Object detected!");
  } else {
    Serial.println("No object detected");
  }

  // Wait for a short time before reading again
  delay(500);
}
