#include <WiFi.h>
#include <esp_now.h>
#include <ESP32Servo.h>

Servo myservo;

float c_kp = 1.0, c_ki = 0.0, c_kd = 0.0;
float prev_error = 0, integral = 0;

float received_angle = 0;

typedef struct struct_message {
  float angle;
} struct_message;

struct_message incomingData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataBytes, int len) {
  if (len == sizeof(incomingData)) {
    memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));
    received_angle = incomingData.angle;
  }
}

void setup() {
  Serial.begin(250000);

  myservo.attach(13);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  Serial.print("Received: ");
  Serial.println(received_angle);

  float pid_output = pid(c_kp, c_ki, c_kd, received_angle, 0);

  pid_output = constrain(pid_output, -90, 90);

  myservo.write(90 + pid_output);

  Serial.print("PID: ");
  Serial.println(pid_output);

  delay(20); 
}

float pid(float kp, float ki, float kd, float actual, float setpoint) {
  float error = actual - setpoint;

  integral += error;
  float derivative = error - prev_error;

  float output = (kp * error) + (ki * integral) + (kd * derivative);

  prev_error = error;

  return output;
}