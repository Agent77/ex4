#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

#include "Point.h"
class Passenger {
private:
    Point source;
    Point dest;
public:
    Passenger() {};
    Passenger(Point p, Point p2);
    ~Passenger() {}
    int rateDriver();
    Point getSource();
    Point getDestination();
};


#endif //EX2_PASSENGER_H
