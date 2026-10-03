#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TCS3472.h>

// Create an instance of the TCS3472 sensor
Adafruit_TCS3472 tcs;

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the TCS3472 sensor
  if (!tcs.begin()) {
    Serial.println("Sensor not detected. Please check your wiring.");
    while (1);
  }

  // Enable the sensor (this is done automatically by tcs.begin(), but it's good practice to set it explicitly)
  tcs.setInterrupt(false);  // Enable the interrupt (to allow the sensor to take readings)
  delay(1000);  // Delay for initialization
}

void loop() {
  uint16_t clear, red, green, blue;

  // Get the color data from the sensor
  tcs.getRawData(&red, &green, &blue, &clear);

  // Print the raw color data
  Serial.print("Red: "); Serial.print(red); 
  Serial.print("\tGreen: "); Serial.print(green); 
  Serial.print("\tBlue: "); Serial.print(blue); 
  Serial.print("\tClear: "); Serial.println(clear);

  // Wait for a short period before taking the next reading
  delay(500);
}