#ifndef Password_h
#define Password_h

#include <Arduino.h>

class Password{
    private:
        char passcode[5];
        char pass_input[6];
        int cursor = 0;
    public:
        Password(char passcode[]);
        char* getInputPass();
        void inputKey(char key);
        bool checkPass();
        void clearPass();
};


#endif