TaskHandle_t Task1;
TaskHandle_t Task2;

// LED pins
const int led1 = 2;

void setup() {
  Serial.begin(115200); 
  pinMode(led1, OUTPUT);
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0);
  xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,1);
}

//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led1, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    delay(1000);
  } 
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
   Serial.print("hi");
   delay(500);
  }
}

void loop() {
  
}
