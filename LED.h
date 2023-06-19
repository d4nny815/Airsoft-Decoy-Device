// LED.h
#ifndef LED_h
#define LED_h

#include <Arduino.h>

class LED {
  private:
    int ledPin;
    bool ledState;

  public:
    LED(int pin);
    void turnON();
    void turnOFF();
    void toggle();
};

#endif
