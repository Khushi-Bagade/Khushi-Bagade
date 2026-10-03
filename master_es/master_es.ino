#include <WiFi.h>
#include <esp_now.h>
#include "BNO055_support.h"
#include <Wire.h>

TaskHandle_t TaskSend;
TaskHandle_t TaskSensor;

struct bno055_t myBNO;
struct bno055_euler myEulerData;

typedef struct struct_message {
  float angle;
} struct_message;

struct_message dataToSend;

volatile int n_angle = 0;

uint8_t receiverMAC[] = {0xD4, 0xE9, 0xF4, 0xA4, 0xA7, 0x80};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // Add peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // I2C + BNO055
  Wire.begin();
  BNO_Init(&myBNO);
  bno055_set_operation_mode(OPERATION_MODE_NDOF);

  delay(1000);

  xTaskCreatePinnedToCore(SensorTask,"SensorTask", 10000, NULL, 1, &TaskSensor, 1  );
  xTaskCreatePinnedToCore( SendTask, "SendTask",10000, NULL, 1,&TaskSend,  0  );
}

void loop() {
}

void SensorTask(void *pvParameters) {

  while (1) {

    bno055_read_euler_hrp(&myEulerData);
    int angle = (int)(myEulerData.h / 16.0);
    if (angle > 180) angle -= 360;
    if (angle >= -180 && angle <= 180) {
      n_angle = angle;
    }

    vTaskDelay(20 / portTICK_PERIOD_MS);  
  }
}

void SendTask(void *pvParameters) {

  while (1) {

    dataToSend.angle = (float)n_angle;

    esp_now_send(receiverMAC, (uint8_t *)&dataToSend, sizeof(dataToSend));

    Serial.print("Sent Angle: ");
    Serial.println(n_angle);

    vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
}