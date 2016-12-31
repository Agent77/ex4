#ifndef EX2_TRIP_H
#define EX2_TRIP_H

#include "Point.h"
#include <boost/serialization/access.hpp>
class Trip {
    friend class boost::serialization::access;

    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {
        ar & tripId;
        ar & xStart;
        ar & yStart;
        ar & xEnd;
        ar & yEnd;
        ar & start;
        ar & end;
        ar & numOfPassengers;
        ar & metersPassed;
        ar & tariff;
        ar & startTime;
    }
private:
    int tripId;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    Point* start;
    Point* end;
    int numOfPassengers;
    int metersPassed;
    double tariff;
    int startTime;

public:
    Trip();
    Trip(int tripId, int xStart, int yStart, int xEnd, int yEnd, int numOfPassengers, double tariff, int time);
    ~Trip();
    int getId();
    int getMeters();
    int getNumOfPassengers();
    double getTariff();
    void addMeters();
    Coordinate* getStart();
    Coordinate* getEnd();
    void updateStartPoint(Coordinate *c);
    int getTripTime();

};


#endif //EX2_TRIP_H
