#ifndef EX2_TRIP_H
#define EX2_TRIP_H

#include "Point.h"
class Trip {
//c
private:

    int tripId;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    Coordinate* start;
    Coordinate* end;
    int numOfPassengers;
    int metersPassed;
    double tariff;

public:
    Trip();
    Trip(int tripId, int xStart, int yStart, int xEnd, int yEnd, int numOfPassengers, double tariff);
    ~Trip();
    int getId();
    int getMeters();
    int getNumOfPassengers();
    double getTariff();
    void addMeters();
    Coordinate* getStart();
    Coordinate* getEnd();
    void updateStartPoint(Coordinate *c);

};


#endif //EX2_TRIP_H
