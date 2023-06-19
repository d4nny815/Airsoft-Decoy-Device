#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay(int anodes[], int segments[]){
    segLUT[0] = 0x7E;
    segLUT[1] = 0x30;
    segLUT[2] = 0x6D;
    segLUT[3] = 0x79;
    segLUT[4] = 0x33;
    segLUT[5] = 0x5B;
    segLUT[6] = 0x5F;
    segLUT[7] = 0x70;
    segLUT[8] = 0x7F;
    segLUT[9] = 0x7B;

    // Assign the anodes and segments arrays
    this->anodes = anodes;
    this->segments = segments;
}

void SevenSegmentDisplay::SsegSetup(){
    for(int i = 0; i < 4; i++){
        pinMode(anodes[i], OUTPUT);
        digitalWrite(anodes[i], HIGH);
    }
    for(int i = 0; i < 8; i++){
        pinMode(segments[i], OUTPUT);
    }
}

void SevenSegmentDisplay::displayDigit(byte hexVal) {
  int curBit = 7;
  for (int i = 0; i <= 7; i++) {
    byte seg = bitRead(hexVal, curBit);
    curBit--;
    digitalWrite(segments[i], seg);
  }
}

void SevenSegmentDisplay::displaySseg(int val) {
    int bcd = decToBCD(val);
    switch(curDisplayVal){
        case 0:
            displayThousands(bcd >> 12);
            curDisplayVal++;
            break;
        case 1:
            displayHundreds((bcd >> 8) & 0x0F);
            curDisplayVal++;
            break;
        case 2:
            displayTens((bcd >> 4) & 0x0F);
            curDisplayVal++;
            break;
        case 3:
            displayOnes(bcd & 0x0F);
            curDisplayVal = 0;
            break;
    }
}

int SevenSegmentDisplay::decToBCD(int val) {
  int bcd = 0;
  int curBit = 0;
  while (val > 0) {
    int rem = val % 10;
    bcd = bcd + (rem << curBit);
    val = val / 10;
    curBit += 4;
  }
  return bcd;
}

void SevenSegmentDisplay::displayThousands(byte val) {
    // if (val == 0) { return; }
    digitalWrite(anodes[0], LOW);   // turn on anode
    displayDigit(segLUT[val]);      // display digit
    delay(6);                       // delay to prevent flickering
    digitalWrite(anodes[0], HIGH);  // turn off anode
}

void SevenSegmentDisplay::displayHundreds(byte val) {
    // if (val == 0) { return; }
    digitalWrite(anodes[1], LOW);   // turn on anode
    displayDigit(segLUT[val] | 0x80);      // display digit
    delay(6);                       // delay to prevent flickering
    digitalWrite(anodes[1], HIGH);  // turn off anode
}

void SevenSegmentDisplay::displayTens(byte val) {
    // if (val == 0) { return; }
    digitalWrite(anodes[2], LOW);   // turn on anode
    displayDigit(segLUT[val]);      // display digit
    delay(6);                       // delay to prevent flickering
    digitalWrite(anodes[2], HIGH);  // turn off anode
}

void SevenSegmentDisplay::displayOnes(byte val) {
    digitalWrite(anodes[3], LOW);   // turn on anode
    displayDigit(segLUT[val]);      // display digit
    delay(6);                       // delay to prevent flickering
    digitalWrite(anodes[3], HIGH);  // turn off anode
}



