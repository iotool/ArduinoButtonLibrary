/*
 *  https://github.com/iotool/ArduinoButtonLibrary/RohaButton.h
 *  
 *  Library to handle button events (Freeware: use at your own risk).
 *  
 *  History: 
 *  2017-08-03 v1.0 first release
 */

#ifndef ROHABUTTON_h
#define ROHABUTTON_h

#include <Arduino.h>
#include <stdint.h>

class RohaButton {

  public: 
    RohaButton(uint8_t pin);
    RohaButton(uint8_t pin, uint8_t pinMode);
    void setPin(uint8_t pin);
    void setInterrupt(bool interrupt);
    void doInterrupt();
    void doInterrupt(uint32_t uptime);
    bool isPushed();
    bool onStart();
    bool onStop();
    bool onTimeout();
    void setTimeout(uint32_t timeout);
    uint32_t getInterval();

  protected:
    uint8_t _pin;
    uint8_t _pin_mode;
    uint8_t _pin_pushed;
    uint32_t _uptime;
    uint32_t _uptime_timeout;
    uint32_t _uptime_interval;
    bool _interrupt;
    bool _pushed;
    bool _start;
    bool _stop;
    bool _timeout;

  private:
    void _doInitialize();

};

#endif /*ROHABUTTON_h*/