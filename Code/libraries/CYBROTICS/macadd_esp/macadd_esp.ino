#include "BluetoothSerial.h"

BluetoothSerial SerialBT;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");  // Bluetooth device name
  Serial.println("ESP32 Bluetooth Started.");
   uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_BT);
  Serial.printf("Bluetooth MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}



void loop() {
}
