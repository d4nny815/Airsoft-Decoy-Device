#include "Password.h"

Password::Password(char passcode[]){
    this->passcode[0] = passcode[0];
    this->passcode[1] = passcode[1];
    this->passcode[2] = passcode[2];
    this->passcode[3] = passcode[3];
    this->passcode[4] = passcode[4];
    this->pass_input[0] = 'A';
    this->pass_input[1] = 'A';
    this->pass_input[2] = 'A';
    this->pass_input[3] = 'A';
    this->pass_input[4] = 'A';
    this->pass_input[5] = '\0';
    return;
}

char* Password::getInputPass(){
    return pass_input;
}

void Password::inputKey(char key){
    if (cursor > 4){
        clearPass();
    }
    pass_input[cursor] = key;
    cursor++;
    return;
}

bool Password::checkPass(){
    Serial.print(pass_input);
    Serial.print("    ");
    Serial.println(passcode);
    for (int i=0; i<5; i++){
        Serial.print(pass_input[i]);
        Serial.print("    ");
        Serial.println(passcode[i]);
        if (passcode[i] != pass_input[i]){
            clearPass();
            return false;
        }
    }
    return true;
}

void Password::clearPass(){
    cursor = 0;
    pass_input[0] = 'A';
    pass_input[1] = 'A';
    pass_input[2] = 'A';
    pass_input[3] = 'A';
    pass_input[4] = 'A';
    return;
}

