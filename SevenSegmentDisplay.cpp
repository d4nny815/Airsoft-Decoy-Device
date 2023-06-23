#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay(int anodes[], int segments[]){
    int segLUTvals[] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B};
    byte bcdLUTvals[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
    for (int i=0; i<10; i++){
        segLUT[i] = segLUTvals[i];
        bcdLUT[i] = bcdLUTvals[i];
    }

    // Assign the anodes and segments arrays
    this->anodes = anodes;
    this->segments = segments;
}

void SevenSegmentDisplay::SsegSetup(){
    for(int i=0; i<4; i++){ 
        pinMode(anodes[i], OUTPUT);
        digitalWrite(anodes[i], LOW); 
    }
    for(int i=0; i<8; i++){ 
        pinMode(segments[i], OUTPUT);
        digitalWrite(segments[i], HIGH);
        delay(25);
    }

    // Test the display
    for (int i=0; i<4; i++){
		turnOnAnode(i);
		for (int j=0; j<10; j++){
			debugDigit(j);
			delay(25);
		}
	}
    clearDisplay();
}

void SevenSegmentDisplay::debugDigit(byte val){ // val between 0 and 9
    displayDigit(segLUT[val]);
}

void SevenSegmentDisplay::displayDigit(byte hexVal) {
  for (int i = 0; i <= 7; i++) {
    byte seg = bitRead(hexVal, 7 - i);
    digitalWrite(segments[i], seg);
  }
}

void SevenSegmentDisplay::clearDisplay() {
  for (int i = 0; i <= 4; i++) {
    digitalWrite(anodes[i], HIGH);
  }
}

void SevenSegmentDisplay::turnOnAnode(byte anode) {  // anode from 0 to 3
    for (int i=0; i<4; i++){
        digitalWrite(anodes[i], (i == anode) ? LOW : HIGH);
    }
}

void SevenSegmentDisplay::displaySseg(int val) {
    unsigned int bcd = decToBCD(val);
    switch(curDisplayVal){
        case 0:
            displayThousands(bcd);
            curDisplayVal++;
            return;
        case 1:
            displayHundreds(bcd);
            curDisplayVal++;
            return;
        case 2:
            displayTens(bcd);
            curDisplayVal++;
            return;
        case 3:
            displayOnes(bcd);
            curDisplayVal = 0;
    }
}

unsigned int SevenSegmentDisplay::decToBCD(unsigned int val) {
    int bcd = 0;
    int shift = 0;
    do {
        byte digit = val % 10;
        bcd |= bcdLUT[digit] << shift;
        val /= 10;
        shift += 4;
    } while (val != 0);
    return bcd;
}

void SevenSegmentDisplay::displayThousands(unsigned int val) {
    byte thousands = val >> 12;
    if (thousands != 0){
        displayDigit(segLUT[thousands]);
        turnOnAnode(0);
    }
    return;
}

void SevenSegmentDisplay::displayHundreds(unsigned int val) {
    byte hundreds = (val >> 8) & 0x000F;
    if (val > 0x1000 || hundreds != 0){
        displayDigit(segLUT[hundreds]);
        turnOnAnode(1);
    }
    return;
}

void SevenSegmentDisplay::displayTens(unsigned int val) {
    byte tens = (val >> 4) & 0x000F;
    if (val > 0x0010 || tens != 0){
        displayDigit(segLUT[tens]);
        turnOnAnode(2);
    }
    return;
}

void SevenSegmentDisplay::displayOnes(unsigned int val) {
    byte ones = val & 0x000F;
    displayDigit(segLUT[ones]);
    turnOnAnode(3);
    return;
}




