//
// Created by nirbs on 27/12/16.
//

#ifndef PRACTICE6_CLOCK_H
#define PRACTICE6_CLOCK_H
#include <boost/serialization/access.hpp>

class Clock {
private:
    int time;
public:
    Clock();
    int getTime();
    void increaseTime();

};


#endif //PRACTICE6_CLOCK_H
