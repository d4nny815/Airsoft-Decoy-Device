#ifndef lcd_h
#define lcd_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

byte cursor = 0;

void lcd_init(){
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("FAKE BOMB");
    delay(125);
    return;
}

void lcd_clear(){
    lcd.clear();
    delay(100);
    return;
}

void lcd_enter_time(char* time){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter time: MM:SS");
    lcd.setCursor(0,1);
    lcd.print(time);
    return;
}

void lcd_print(char* message1, char* message2){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(message1);
    lcd.setCursor(0,1);
    lcd.print(message2);    
    return;
}

void lcd_print(char* message){
    lcd.setCursor(0,1);
    lcd.print(message);
    return;
}


void lcd_print_display(char* message){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(message);
    return;
}

void lcd_enter_pass(char* pass){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter passcode:");
    lcd.setCursor(0,1);
    lcd.print(pass);
    return;
}


#endif