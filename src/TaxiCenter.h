//
// Created by Tiki Lobel on 11/29/16.
//

#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H

#include "Trip.h"
#include "Driver.h"
#include "Point.h"
#include <vector>

using namespace std;
/*
 * class that controls all drivers/taxis in alerting them
 * to move, assigning trips, and getting locations
 */
class TaxiCenter {
    friend class boost::serialization::access;

    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {
        ar & drivers;
        ar & taxis;
        ar & locations;
        ar & started;
    }
private:
    std::vector<Driver> drivers;
    std::vector<Taxi> taxis;
    Point* locations;
    std::vector<Trip> trips;
    Graph* map;
    bool started;
public:
    TaxiCenter();
    TaxiCenter(Graph* map1);
    ~TaxiCenter() {};
    int assignDrivers();
    void driveAll();
    Driver findClosestDriver(Trip t);
    void addDriver(int driverId, int age, char mStatus, int vehicleId, int exp);
    void addTrip(Trip t);
    void updateMeters();
    int checkDestinations();
    void requestDriverLocation(int driverId);
    vector <Driver> getDrivers();
    vector<Trip> getTrips();
    void addTaxi(Taxi t);
    void addDriver(Driver d);
    void updateDriverTrip(Trip newTrip);
    Taxi assignTaxi(int driverId);
    Trip getNextTrip (int currentTime);
    int checkTripTimes(int currentTime);
};


#endif //EX2_TAXICENTER_H
