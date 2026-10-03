int jo = 3;
int jc = 4;
int p = 5;
int a;

void setup() {
  Serial.begin(115200);
  pinMode(jo, OUTPUT);
  pinMode(jc, OUTPUT);
  pinMode(p, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    a = Serial.parseInt();
  }
  if (a == 1) {
    digitalWrite(jo, HIGH);  // open
    delay(500);
    digitalWrite(p, HIGH);  // Activate
    delay(500);
    digitalWrite(p, LOW);  // Deactivate
    delay(500);
    digitalWrite(jo, LOW);  // Close
    delay(500);
  }
  Serial.println(a);
}
