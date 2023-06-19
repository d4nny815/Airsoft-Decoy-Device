#ifndef Time_h
#define Time_h

#include <Arduino.h>

class Time{
    private:
        int min;
  	    int sec;
        char time_arr[5];
        int cursor = 0;
    public:
        int getTime();
        char* getTimeArr(){return time_arr;}
        Time(int min, int sec);  // constructor
        void inputTime(char customKey);
        bool setTime();
        void clearTime();
        bool decrementTime();
};

#endif

