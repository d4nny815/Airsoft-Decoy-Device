#include "Buzzer.h"

Buzzer::Buzzer(int pin) {
  buzzerPin   = pin;
  buzzerState = false;
  pinMode(buzzerPin, buzzerState);
}

void Buzzer::HighPitch() {
    buzzerState = true;
    tone(buzzerPin, 1800);
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
  if (buzzerState == true){
      HighPitch();
  }
  else{
      noTone(buzzerPin);
  }
}



