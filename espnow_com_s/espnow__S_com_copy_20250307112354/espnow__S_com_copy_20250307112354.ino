#include <esp_now.h>
#include <WiFi.h>

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_err_t status = esp_now_init();
  esp_now_register_send_cb(OnDataSent);

  if (status != ESP_OK) {
    Serial.print("ESP-NOW initialization failed with error code: ");
    Serial.println(status);
    return;
  }
}
void OnDataSent(const uint8_t* peer_mac_addr, esp_now_send_status_t status) {

  Serial.println("Data sent!");

  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Send success");
  } else {
    Serial.println("Send failed");
  }
}

uint8_t broadcastAddress[] = { 0x94, 0x54, 0xC5, 0xA9, 0x4A, 0x52 };

void loop() {

  const char* data = "hello";
  Serial.println(data);
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*)data, strlen(data));
  if (result == ESP_OK) {
    Serial.println("sending data");
  } else {
    Serial.println("error");
  }
}
