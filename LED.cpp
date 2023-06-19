// LED.cpp
#include "LED.h"

LED::LED(int pin) {
  ledPin   = pin;
  ledState = false;
  pinMode(ledPin, OUTPUT);
}

void LED::turnON() {
  ledState = true;
  digitalWrite(ledPin, ledState);
}

void LED::turnOFF() {
  ledState = false;
  digitalWrite(ledPin, ledState);
}

void LED::toggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}
