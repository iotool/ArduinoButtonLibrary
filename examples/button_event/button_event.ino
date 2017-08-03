/*
 *  https://github.com/iotool/ArduinoButtonLibrary/examples/button_event/
 *  
 *  History: 
 *  2017-08-03 v1.0 first release
 */
 

#include <RohaButton.h>

RohaButton pushButton(4);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (pushButton.onStart()) {
    Serial.print("onStart: interval stop->start "); 
    Serial.println(pushButton.getInterval());
    pushButton.setTimeout(500);
  }
  if (pushButton.onTimeout()) {
    if (pushButton.isPushed()) {
      Serial.print("onTimeout: pressed for 500 ms "); 
    }
  }
  if (pushButton.onStop()) {
    Serial.print("onStop: interval start->stop "); 
    Serial.println(pushButton.getInterval());
  }
}