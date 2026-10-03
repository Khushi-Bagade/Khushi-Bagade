
TaskHandle_t Task1;
TaskHandle_t Task2;

// #define ledpin 2

void setup() {
  xTaskCreatePinnedToCore( Task1Code, "Task1", 10000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore( Task2Code, "Task2", 10000, NULL, 1, &Task2, 1);
  Serial.begin(9600);
  // pinMode(2,OUTPUT);
}

void loop() {   
}

void Task1Code(void *parameters){
  while(true){
    Serial.println("khushi");
  // digitalWrite(ledpin,HIGH);
  vTaskDelay(2000);
  // digitalWrite(ledpin,LOW);
  // vTaskDelay(2000);
  Serial.println("task running on core:");
  Serial.println(xPortGetCoreID());
}
}

void Task2Code(void *parameters){
  while(true){
  Serial.println("hello");
  vTaskDelay(2000);
  Serial.println("task running on core:");
  Serial.println(xPortGetCoreID());
  }
}

