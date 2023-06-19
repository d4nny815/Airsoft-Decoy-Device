// SevenSegmentDisplay.h
#ifndef SevenSegmentDisplay_h
#define SevenSegmentDisplay_h

#include <Arduino.h>

class SevenSegmentDisplay{
    private:
        int segLUT[10];
        int* anodes;
        int* segments;
        byte curDisplayVal = 0;
        int decToBCD(int val);
        void displayDigit(byte hexVal);
        void displayThousands(byte val);
        void displayHundreds(byte val);
        void displayTens(byte val);
        void displayOnes(byte val);
    public:
        SevenSegmentDisplay(int anodes[], int segments[]);  // constructor
        void SsegSetup();
        void displaySseg(int val);
      
};

#endif

