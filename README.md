# ArduinoButtonLibrary

Easy to use button library for Arduino IDE (avr, esp8266).

* state isPushed: button is pushed down
* event onStart: button pressed
* event onStop: button released
* event onTimeout: detect short click / long push / confirm timeout
* default pinmode: INPUT_PULLUP (push = LOW)
* advanced: external interrupt handling to share one timer
* advanced: change pin to support device flip
* handle multiple buttons
