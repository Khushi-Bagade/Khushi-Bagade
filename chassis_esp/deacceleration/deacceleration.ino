unsigned long cur_s = 0;
unsigned long pre_s = 0;
int speed = 150;           // starting speed (higher than target)
int target = 0;          // target speed

int daccln(int, int, int);  // correct function declaration

void setup() {
  Serial.begin(9600);
}

void loop() {
  speed = daccln(speed, 10, target); // decrease every 10 ms
  Serial.println(speed);
}

int daccln(int av, int interval, int stpt) {
  cur_s = millis();

  if (cur_s - pre_s >= interval && av > stpt) {
    av -= 1;               // deacccelerate
    pre_s = cur_s;
  }

  return av;
}


