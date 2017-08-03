/*
 *  https://github.com/iotool/ArduinoButtonLibrary/RohaButton.cpp
 *  
 *  Library to handle button events (Freeware: use at your own risk).
 *  
 *  History: 
 *  2017-08-03 v1.0 first release
 */

/*
 *  https://github.com/iotool/ArduinoButtonLibrary/RohaButton.h
 *  
 *  History: 
 *  2017-08-03 v1.0 first release
 */

#include "RohaButton.h"

RohaButton::RohaButton(uint8_t pin) {
  this->_pin = pin;
  this->_pin_mode = INPUT_PULLUP;
  this->_pin_pushed = LOW;
  this->_doInitialize();
}

RohaButton::RohaButton(uint8_t pin, uint8_t pin_mode) {
  this->_pin = pin;
  this->_pin_mode = pin_mode;
  switch(this->_pin_mode) {
    case INPUT: this->_pin_pushed = HIGH; break;
    case INPUT_PULLUP: this->_pin_pushed = LOW; break;
  }
  this->_doInitialize();
}

void RohaButton::_doInitialize() {
  pinMode(this->_pin,this->_pin_mode);
  this->_uptime = 0;
  this->_uptime_timeout = 0;
  this->_uptime_interval = 0;
  this->_interrupt = false;
  this->_pushed = false;
  this->_start = false;
  this->_stop = false;
  this->_timeout = false;
}

void RohaButton::setPin(uint8_t pin) {
  this->_pin = pin;
}

void RohaButton::doInterrupt() {
  uint32_t uptime = millis();
  this->doInterrupt(uptime);
}

void RohaButton::doInterrupt(uint32_t uptime) {
  if (this->_uptime != uptime) {
    // reduce workload (check state once every millisecond)
    if (digitalRead(this->_pin) == this->_pin_pushed) {
      if (!this->_pushed) {
        // onStart
        this->_start = true;
        this->_stop = false;
        this->_uptime_timeout = 0;
      } else if (this->_start) {
        // setStartInterval
        this->_uptime_interval = uptime;
        this->_start = false;
      }
      this->_pushed = true;
    } else {
      if (this->_pushed) {
        // onStop
        this->_start = false;
        this->_stop = true;
        this->_uptime_timeout = 0;
      } else if (this->_stop) {
        // setStopInterval
        this->_uptime_interval = uptime;
        this->_stop = false;
      }
      this->_pushed = false;
    }
    if (this->_uptime_timeout == 0) {
      this->_timeout = false;
    } else {
      if (this->_uptime_timeout <= this->_uptime) {
        // onTimeout
        this->_timeout = true;
        this->_uptime_timeout = 0;
      }
    }
    this->_uptime = uptime;
  }
}

void RohaButton::setInterrupt(bool interrupt) {
  this->_interrupt = interrupt;
}

uint32_t RohaButton::getInterval() {
  return this->_uptime - this->_uptime_interval;
}

void RohaButton::setTimeout(uint32_t timeout) {
  this->_uptime_timeout = this->_uptime + timeout;
  if (this->_uptime_timeout == 0) this->_uptime_timeout = 1;
  this->_timeout = false;
}

bool RohaButton::isPushed() {
  if (!this->_interrupt) this->doInterrupt();
  return this->_pushed;
}

bool RohaButton::onStart() {
  if (!this->_interrupt) this->doInterrupt();
  return this->_start;
}

bool RohaButton::onStop() {
  if (!this->_interrupt) this->doInterrupt();
  return this->_stop;
}

bool RohaButton::onTimeout() {
  if (!this->_interrupt) this->doInterrupt();
  return this->_timeout;
}
