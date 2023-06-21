#include "Time.h"

Time::Time(int min, int sec){
    time_arr[0] = '0';
    time_arr[1] = '0';
    time_arr[2] = ':';
    time_arr[3] = '0';
    time_arr[4] = '0';
    time_arr[5] = '\0';
    this->min = min;
    this->sec = sec;
}
int Time::getTime(){
    return (min * 100) + sec;
}

void Time::inputTime(char customKey){
    if (cursor > 4){
        clearTimeArr();
        return;
    }
    
    time_arr[cursor] = customKey;
    cursor++;
    return;
}

char* Time::getTimeArr(){
    return time_arr;
}

bool Time::setTime(){
    if (time_arr[2] != ':'){
      	clearTime();
        return false;
    }
    min = (time_arr[0] - '0') * 10 + (time_arr[1] - '0');
    sec = (time_arr[3] - '0') * 10 + (time_arr[4] - '0');
    if (min > 60 || sec > 60){
      	clearTime();
        return false;
    }
    this->min = min;
    this->sec = sec;
    return true;
}

void Time::clearTimeArr(){
    cursor = 0;
    time_arr[0] = '0';
    time_arr[1] = '0';
    time_arr[2] = ':';
    time_arr[3] = '0';
    time_arr[4] = '0';
    return;
}

void Time::clearTime(){
    cursor = 0;
    min = 0;
    sec = 0;
    return;
}

bool Time::decrementTime(){
    if (sec == 0){
        if (min == 0){
            return true;
        }
        else{
            min--;
            sec = 59;
        }
    }
    else{
        sec--;
    }
    return false;
}

