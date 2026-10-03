#include <esp_now.h>
#include <WiFi.h>

 esp_now_send_status_t sendStatus;
 int status;

 void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  
  uint8_t broadcastAddress[]={0x94 , 0x54 , 0xC5 , 0xA9 , 0x4A , 0x52};
  
  if (status != ESP_OK) {
    Serial.print("ESP-NOW initialization failed with error code: ");
    Serial.println(status);
   
    return;
    esp_now_register_send_cb(OnDataSent);
 }
 }
 void loop(){
const char* data  = ("hello");
Serial.println("data");

 }

 void OnDataSent(const uint8_t* peer_mac_addr){
  Serial.println("data sent:");
   if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Send success");
  } else {
    Serial.println("Send failed");
  }
}