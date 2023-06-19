#ifndef Buzzer_h
#define Buzzer_h

#include <Arduino.h>
class Buzzer{
    private:
        int buzzerPin;
        bool buzzerState;
    public:
        Buzzer(int pin);
        void HighPitch();
        void LowPitch();
        void turnOFF();
        void toggle();
};


#endif