unsigned long cur_s = 0;
unsigned long pre_s = 0;
int speed = 0 , target = 150 ;

int accln(int) ; //function declaration

void setup() {
  Serial.begin(9600);
}

void loop() {
  speed = accln(speed,10,target);
  Serial.println(speed);
}

int accln(int av , int interval , int stpt) { 
    cur_s = millis();

  if (cur_s - pre_s >= interval && av < stpt) {
    av += 1;
    pre_s = cur_s;
  }
  return av ;
}

