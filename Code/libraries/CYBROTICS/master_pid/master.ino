#include "Arduino_NineAxesMotion.h"        
#include <Wire.h>


NineAxesMotion mySensor;         
unsigned long lastStreamTime = 0; 
const int streamPeriod = 20;     
int hd;  
 int a;
 int b;
 int c;  

void setup() 
{
  
  Serial.begin(9600);          
  Wire.begin(7);                    
  //Sensor Initialization
  mySensor.initSensor();        
  mySensor.setOperationMode(OPERATION_MODE_NDOF);   
  mySensor.setUpdateMode(MANUAL);	
}

void loop(){
mySensor.updateEuler();        
mySensor.updateCalibStatus();
int hd = mySensor.readEulerHeading() ;

a=(hd / 100);
b=((hd % 100) / 10);
c=(hd % 10);

Wire.beginTransmission(7);

Wire.write(a);
Wire.write(b);
Wire.write(c);

Wire.endTransmission(7);

Serial.print("hd: ");
Serial.println(hd);
Serial.print("a: ");
Serial.println(a);
Serial.print("b: ");
Serial.println(b);
Serial.print("c: ");
Serial.println(c);
}

