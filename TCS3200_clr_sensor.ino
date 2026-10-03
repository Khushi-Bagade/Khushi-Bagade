// Pin definitions
int S0 = 4;
int S1 = 5;
int S2 = 6;
int S3 = 7;
int sensorOut = 8;

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize the control pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 100% (for maximum resolution)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
}

void loop() {
  // Reading Red value
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int red = pulseIn(sensorOut, LOW);  // Measure the pulse width

  // Reading Green value
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int green = pulseIn(sensorOut, LOW);  // Measure the pulse width

  // Reading Blue value
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int blue = pulseIn(sensorOut, LOW);  // Measure the pulse width

  // Print the RGB values to the Serial Monitor
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print("\tGreen: ");
  Serial.print(green);
  Serial.print("\tBlue: ");
  Serial.println(blue);

  // Wait before the next reading
  delay(500);
}
