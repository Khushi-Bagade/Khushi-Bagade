// #include<ACE128.h>
// #include <Wire.h>  

// int cpos;
// int lpos;
// int revolutioncount = 0;

// void setup() {
//   Serial.begin(9600);
//   encoder.begin();
//   lpos = encoder.read();
//   }

// void loop() {
//   lpos = encoder.read(); 
//   if (lpos > 100 && cpos < 20) {
//     revolutioncount++;                  //increase 127>0
//   }

//   else if (lpos < 20 && cpos > 100) {  //decrease 0>127   
//   revolutioncount--;
//     }
//     lpos = cpos;
//     Serial.print("position:");
//     Serial.println("position");
//     Serial.print("revolution:");
//     Serial.println("revolution");
// }

// #########################################################################################################################################################################################################################
// 
// PCF8574 0x20
#define ACE_ADDR 0x20 

#include <ACE128.h>  // Include the ACE128.h from the library folder
#include <ACE128map87654321.h> // mapping for pin order 87654321

ACE128 myACE(ACE_ADDR, (uint8_t*)encoderMap_87654321); // I2C without using EEPROM
uint8_t oldPos = 255;
uint8_t upos;
int8_t pos;
int16_t mpos;

void setup() {
  Serial.begin(9600);
  myACE.begin();    // this is required for each instance, initializes the pins
}


void loop() {
  pos = myACE.pos();                 // get logical position - signed -64 to +63
  upos = myACE.upos();               // get logical position - unsigned 0 to +127
  mpos = myACE.mpos();               // get multiturn position - signed -32768 to +32767

  if (upos != oldPos) {            // did we move?
    oldPos = upos;                 // remember where we are
    Serial.print(" pos ");
    Serial.print(pos, DEC);
    Serial.print(" upos ");
    Serial.print(upos, DEC);
    Serial.print(" mpos ");
    Serial.println(mpos, DEC);
  }
}
