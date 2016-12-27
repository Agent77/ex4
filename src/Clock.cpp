//
// Created by nirbs on 27/12/16.
//

#include "Clock.h"
Clock::Clock(){
    time=0;
}

int Clock::getTime() {
    return time;
}

void Clock::increaseTime() {
    time++;
}