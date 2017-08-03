/*
 *  https://github.com/iotool/ArduinoButtonLibrary/examples/button_simple/
 *  
 *  History: 
 *  2017-08-03 v1.0 first release
 */
 
#include <RohaButton.h>

RohaButton pushButton(4);

void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  if (pushButton.isPushed()) {
    digitalWrite(13,HIGH);
  } else {
    digitalWrite(13,LOW);  
  }
}