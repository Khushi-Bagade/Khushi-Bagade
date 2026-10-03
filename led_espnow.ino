#include<esp_now.h>
#include<WiFi.h>

#define ledpin 2

int str[6];
int i;
int esp_ok;
esp_now_peer_info_t peer_info;


void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);

 uint8_t peer_addr[] = ("94:54:c5:a9:1f:ce,6");
  WiFi.mode(WIFI_STA);
  esp_now_init();

  if (esp_now_add_peer(&peer_info) != esp_ok){
  Serial.println("failed to add info");
  esp_now_register_send_cb(onDataSent);

}

void loop() {
}

}
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
  for(i=0;i<=6;i++){
    if(i=0){
      digitalWrite(ledpin,HIGH);
      delay(100);
    }
    if(i=1){
      digitalWrite(ledpin,HIGH);
      delay(200);
    }
    if(i=2){
      digitalWrite(ledpin,HIGH);
      delay(300);
    }
    if(i=3){
      digitalWrite(ledpin,HIGH);
      delay(400);
    }
    if(i=4){
      digitalWrite(ledpin,HIGH);
      delay(500);
    }
    if(i=5){
      digitalWrite(ledpin,HIGH);
      delay(600);
    }
  }
}

