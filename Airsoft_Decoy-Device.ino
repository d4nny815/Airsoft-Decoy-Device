// debugger code
#include <Streaming.h>
// init for system
int systemState = 0;
#include "LED.h"
LED red(39);
LED yellow(40);
LED blue(41);
#include "Buzzer.h"
Buzzer buzzer(38);

// multitask setup
unsigned long currentTime = 0;     //variable for millis()
unsigned long milliMultiplex = 0;  // placeholder
unsigned long milliSecond = 0;     // placeholder
unsigned long milliBuzzer = 0;     // placeholder
unsigned long multiplexDelay = 5;  //multiplex delay in ms
unsigned long secondDelay = 1000;  //1Hz

//init for keypad
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
	{ '1', '2', '3', ':' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
	{ '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 23, 25, 27, 29 };
byte colPins[COLS] = { 31, 33, 35, 37 };
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//init for 7seg digplay
#include "SevenSegmentDisplay.h"
int anodes[] = { 53, 52, 51, 50 };
int segments[] = { 49, 47, 45, 43, 48, 46, 44, 42 };
SevenSegmentDisplay sseg(anodes, segments);

//init for time
#include "Time.h"
Time timer(0, 0);

//init for passcode
#include "Password.h"
Password password("69420");


void setup() {
	Serial.begin(9600);
	Serial << "Starting up..." << endl;
	systemInit();

}

void loop() {
	unsigned long currentTime = millis();
	if (currentTime - milliMultiplex >= multiplexDelay) {
		milliMultiplex = currentTime;
		sseg.displaySseg(timer.getTime());
	}
	switch (systemState) {   
		case (0):
			systemState = enterTime();
			break;
		case (1):
			systemState = countdown();
			break;
		case (2):
			systemState = endGameWin();
			break;
		case (3):
			systemState = endGameLose();
			break;
		default: systemState = systemInit();
	}
}


int enterTime() {
	blue.turnON();
	char customKey = customKeypad.getKey();
	if (customKey) {
		switch (customKey) {
			case ('#'):  // entered time
				if (timer.setTime()) {
					Serial << "Time set to " << timer.getTimeArr() << endl;
					timer.clearTime();
					return 1;  // next state
				}
				// Serial << "Invalid time entered" << endl;
				// TODO: Display to LCD "Invalid time to enter"
				break;
			case ('*'):  // cleared time
				timer.clearTime();
				// Serial << "Time cleared" << endl;
				return 0;
			default:
				timer.inputTime(customKey);
				// TODO: Display time to LCD
				Serial << "Time: " << timer.getTimeArr() << endl;
		}
	}
	return 0;
}

int countdown() {
	yellow.turnON();
	unsigned long currentTime = millis();
	if (currentTime - milliBuzzer >= 125) {
		milliBuzzer = currentTime;
		buzzer.toggle();
	}
	if (currentTime - milliSecond >= secondDelay) {
		milliSecond = currentTime;
		if (timer.decrementTime()) {
			Serial << "Time's up!" << endl;
			// TODO: Display to LCD "Time's up!"
			buzzer.turnOFF();
			return 3;  // next state
		}
	}
	char customKey = customKeypad.getKey();
	if (customKey) {
		switch (customKey) {
			case ('#'):  // back to enter time
				if (password.checkPass()) {
					Serial << "Password correct" << endl;
					// TODO: Display to LCD "Password correct"
					buzzer.turnOFF();
					return 2;  // next state
				}
				Serial << "incorrect password " << endl;
				break;
			case ('*'):  // back to enter passcode
				password.clearPass();
				// Serial << "Password cleared" << endl;
				// TODO: Display to LCD "Password cleared"
				break;
			default:
				password.inputKey(customKey);
				Serial << "Password: " << password.getInputPass() << endl;
				// TODO: Display inputted password to LCD
		}
	}
	return 1;  // same state
}

int endGameWin() {
	red.turnON();
	Serial << "Game won!" << endl;
	// TODO: Display to LCD "Game won!"
	char customKey = customKeypad.getKey();
	if (customKey) {
		return 0;
	}
	return 2;
}

int endGameLose() {
	red.turnON();
	buzzer.LowPitch();
	Serial << "Game Lost!" << endl;
	// TODO: Display to LCD "Game Lost!"
	char customKey = customKeypad.getKey();
	if (customKey) {
		return 0;
	}
	return 3;
}

int systemInit() {
	sseg.SsegSetup();

	red.turnOFF();
	yellow.turnOFF();
	blue.turnOFF();
	buzzer.turnOFF();
	return 0;
}
