#include "Arduino_NineAxesMotion.h"        
#include <Wire.h>

NineAxesMotion mySensor;         
unsigned long lastStreamTime = 0;     
const int streamPeriod = 20;  
 
int a ;  
int setpoint = 40; 
int new_o;     
int k;
int val;
int lastVal = -1; 
bool o_val = false;

void setup() 
{
  Serial.begin(9600);          
  Wire.begin();                   

  // Sensor Initialization
  mySensor.initSensor();       
  mySensor.setOperationMode(OPERATION_MODE_NDOF);  
  mySensor.setUpdateMode(MANUAL);
}

void loop() {
    
 if ((millis() - lastStreamTime) >= streamPeriod) {
     lastStreamTime = millis();
     mySensor.updateEuler();        
    mySensor.updateCalibStatus(); 
    k = mySensor.readEulerHeading();
    Serial.print("a:");
    Serial.println(a);
    Serial.print("\t");
    Serial.print("new_o: ");
    Serial.println(new_o);
    if (Serial.available()) {
      val = Serial.parseInt(); 
       a=k;
      if (val > 0 && val <= 9 && val != lastVal) {
        lastVal = val; 
        o_val = true;
            
        if (k > 0 && k <= 180) {
         Serial.println(k);
        } 
        else if (k >= 180) {
          k = k - 360;
          Serial.println(k);
          
          
        }

        int diff = setpoint - k;
        if(diff != 180){
          if(diff < 180){
            new_o = setpoint + 180;
            if(diff > 180){
              new_o -=360;
            }
            // else {
            //   new_o = setpoint - 180;
            //   // if(new_o < -180){
            //   new_o +=360;
            //   }
            }
          }
        }
      }       
    }
  }








