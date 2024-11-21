#include "MQ135.h"

MQ135 gasSensor = MQ135(A0);
void setup(){
  Serial.begin(9600);      // sets the serial port to 9600
}
void loop(){
  float rzero = gasSensor.getRZero();
  Serial.println(rzero);
  delay(1000);
}