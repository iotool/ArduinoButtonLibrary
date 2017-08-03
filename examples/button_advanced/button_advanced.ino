/*
 *  https://github.com/iotool/ArduinoButtonLibrary/examples/button_advanced/
 *  
 *  History: 
 *  2017-08-03 v1.0 first release
 */
 

#include <RohaButton.h>

RohaButton pushButton(4);

void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  Serial.begin(9600);
  pushButton.setInterrupt(true);
}

void loop() {
  delay(1);
  uint32_t uptime = millis();
  pushButton.doInterrupt(uptime);
  if (pushButton.onStart()) {
    // onStart: led on
    Serial.print("onStart: stop-start interval ");
    Serial.println(pushButton.getInterval());
    digitalWrite(13,HIGH);
    pushButton.setTimeout(300);
  }
  if (pushButton.onStop()) {
    // onStop: led off or on
    Serial.print("onStop: start-stop interval ");
    Serial.println(pushButton.getInterval());
    if (pushButton.getInterval()<300) {
      // afterShortClick: led off
      digitalWrite(13,LOW);
    } else {
      // afterLongPush: led on
      digitalWrite(13,HIGH);  
      pushButton.setTimeout(500);
    }
  }
  if (pushButton.onTimeout()) {
    if (pushButton.isPushed()) {
      // duringLongPush: blink led
      switch(digitalRead(13)) {
        case HIGH: digitalWrite(13,LOW); break;
        case LOW: digitalWrite(13,HIGH); break;
      }
      pushButton.setTimeout(50);   
    } else {
      // afterStop: led off
      digitalWrite(13,LOW);
    }
  }
}