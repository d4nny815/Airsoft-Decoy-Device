// SevenSegmentDisplay.h
#ifndef SevenSegmentDisplay_h
#define SevenSegmentDisplay_h

#include <Arduino.h>

class SevenSegmentDisplay{
    private:
        int segLUT[10];
        byte bcdLUT[10];
        int* anodes;
        int* segments;
        byte curDisplayVal = 0;
        void debugDigit(byte val); 
        int decToBCD(unsigned int val);
        void displayDigit(byte hexVal);
        void clearDisplay();
        void displayThousands(unsigned int val);
        void displayHundreds(unsigned int val);
        void displayTens(unsigned int val);
        void displayOnes(unsigned int val);
    public:
        void turnOnAnode(byte anode);
        SevenSegmentDisplay(int anodes[], int segments[]);  // constructor
        void SsegSetup();
        void displaySseg(int val);
      
};

#endif

