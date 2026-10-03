#include <SPI.h>
#include <LoRa.h>

#define ss 5
#define rst 14
#define dio0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");

  // Setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  while (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed...");
    delay(500);
  }

  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  Serial.println("Type a message and press Enter to send via LoRa:");
}

void loop() {
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    message.trim(); // Remove any trailing newline or space

    if (message.length() > 0) {
      sendPacket(message);
    }
  }
}

void sendPacket(String message) {
  Serial.print("Sending packet: ");
  Serial.println(message);

  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  Serial.println("Message sent!\n");
}
