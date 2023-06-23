// debugger code
#include <Streaming.h>

// init for system
int systemState;
#include "LED.h"
LED red(39);
LED yellow(40);
LED blue(41);
#include "Buzzer.h"
Buzzer buzzer(13);

// multitask setup
unsigned long currentTime = 0;
unsigned long milliMultiplex = 0;  
unsigned long milliSecond = 0;     
unsigned long milliBuzzer = 0;     
unsigned long multiplexDelay = 3;  //multiplex delay in ms
unsigned long secondDelay = 1000;
unsigned long buzzerDelay = 150;

//init for keypad
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
	{ '1', '2', '3', ':' },
	{ '4', '5', '6', ':' },
	{ '7', '8', '9', ':' },
	{ '*', '0', '#', '#' }
};
byte rowPins[ROWS] = { 23, 25, 27, 29 };
byte colPins[COLS] = { 31, 33, 12, 37 };
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//init for 7seg digplay
#include "SevenSegmentDisplay.h"
int anodes[] = { 50, 51, 52, 53 };
int segments[] = { 49, 47, 45, 43, 48, 46, 44, 42 };
SevenSegmentDisplay sseg(anodes, segments);

//init for LCD
#include "lcd.h"


//init for time
#include "Time.h"
Time timer(0, 0);

//init for passcode
#include "Password.h"
Password password("69420");


void setup() {
	Serial.begin(9600);
	systemState = 0;
	lcd_init();
  Serial << "Setup" << endl;
	sseg.SsegSetup();
}

void loop() {
	// while (true)
	// {
	// 	char customKey = customKeypad.getKey();
	// 	if (customKey) {
	// 		Serial << customKey << endl;
	// 	}
	// }
	

	unsigned long currentTime = millis();
	if (currentTime - milliMultiplex >= multiplexDelay) {
		milliMultiplex = currentTime;
		sseg.displaySseg(timer.getTime());
	}
	switch (systemState) {   
		case (0):
			systemState = enterTimeInit();
			break;
		case(1):
			yellow.toggle();
			systemState = enterTime();
			break;
		case (2):
			red.toggle();
			systemState = countdown();
			break;
		case (3):
			blue.toggle();
			systemState = endGameWin();
			break;
		case (4):
			systemState = endGameLose();
			break;
		case(5):
			systemState = waitForReset();
			break;
		default: setup();
	}
}


int enterTimeInit(){ // state 0
	lcd_print("Enter time:MM:SS", "");
	buzzer.turnOFF();
	return 1;
}

int enterTime() { // state 1
	char customKey = customKeypad.getKey();
	if (customKey) {
		switch (customKey) {
			case ('#'): // enter time
				if (timer.setTime()) {	
					String my_str = "Time set: " + String(timer.getTimeArr()); // if it works it works
					lcd_print(my_str.c_str(), "");
					timer.clearTimeArr();
					return 2;  // next state
				}
				lcd_print("Invalid time");
				timer.clearTimeArr();
				delay(500);
				enterTimeInit();
				break;
			case ('*'):  // cleared time
				timer.clearTimeArr();
				enterTimeInit();
				return 1;
			default: // input time
				timer.inputTime(customKey);
				Serial << timer.getTimeArr() << endl;
				lcd_print(timer.getTimeArr());
		}
	}
	return 1;  // remain in same state
}



int countdown() { // state 2
	unsigned long currentTime = millis();
	if (currentTime - milliBuzzer >= buzzerDelay) {
		milliBuzzer = currentTime;
		buzzer.toggle();
	}
	if (currentTime - milliSecond >= secondDelay) {
		milliSecond = currentTime;
		if (timer.decrementTime()) {
			lcd_print("Time's up!", "");
			delay(1000);
			buzzer.turnOFF();
			return 4;  // next state
		}
	}
	
	char customKey = customKeypad.getKey();
	if (customKey) {
		switch (customKey) {
			case ('#'): 
				if (password.checkPass()) {
					lcd_print("Correct", "Password");
					buzzer.turnOFF();
					delay(500);
					return 3;  // next state
				}
				lcd_print("Incorrect", "Password");
				delay(500);
				password.clearPass();
				lcd_print("Password:", "");
				break;
			case ('*'):  // back to enter passcode
				password.clearPass();
				lcd_print("Password:", "");
				break;
			default:
				password.inputKey(customKey);
				lcd.print(customKey);
		}
	}
	return 2;  // same state
}


int endGameWin() { // state 3
	lcd_print("Game won!", "Press any key");
	return 5;
}

int endGameLose() { // state 4
	buzzer.LowPitch();
	lcd_print("Game Lost!", "Press any key");
	return 5;
}

int waitForReset(){ // state 5
	char customKey = customKeypad.getKey();
	if (customKey) {
		timer.clearTime();
		return 0;
	}
	return 5;
}


