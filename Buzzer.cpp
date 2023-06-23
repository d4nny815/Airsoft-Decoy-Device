#include "Buzzer.h"

Buzzer::Buzzer(int pin) {
  buzzerPin   = pin;
  buzzerState = false;
  pinMode(buzzerPin, buzzerState);
}

void Buzzer::HighPitch() {
    buzzerState = true;
    tone(buzzerPin, 2200);
}

void Buzzer::LowPitch() {
    buzzerState = true;
    tone(buzzerPin, 100);
}

void Buzzer::turnOFF() {
  buzzerState = false;
  noTone(buzzerPin);
}

void Buzzer::toggle() {
  buzzerState = !buzzerState;
  if (buzzerState){
      HighPitch();
  }
  else{
      noTone(buzzerPin);
  }
}



