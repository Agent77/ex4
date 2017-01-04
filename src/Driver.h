#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include <vector>
#include <boost/serialization/access.hpp>
#include "Trip.h"
#include "Passenger.h"
#include "Taxi.h"
/*
 * Driver class represents a driver. It holds the driver fields and
 * in charge of moving on the graph.
 */
class Driver {
    friend class boost::serialization::access;

    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {
        ar & driverId;
        ar & age;
        ar & maritalStatus;
        ar & exp;
        ar & vehicleId;
    }
private:
    int driverId;
    int age;
    int numberOfcustomers;
    int exp;
    int vehicleId;
    double totalRate;
    double avgSatisfaction;
    char maritalStatus;
    Graph* gps;
    Taxi taxi;
    Trip myTrip;
   // std::vector <Passenger> myPassengers;

public:
    Driver();
    ~Driver();
    //Driver(int driverId, int age, char mStatus, int exp, int vehicleId, Graph* gps);
    Driver(int driverId, int age, char mStatus, int exp, int vehicleId);
    int getAge();
    int getVehicleId();
    int getDriverId();
    int getExp() {
        return exp;
    };
    double getSatisfaction();
    Taxi getTaxi();
    Trip* getTrip();
    vector <Passenger> getPassengers();
    char getMaritalStatus();
    void setTaxi(Taxi t);
    void setTrip(Trip t);
    void rateMe(int rating);
    void addPassenger(Passenger p);
    Trip drive();
    bool arrived();
    void setMap(Graph* map);
    void needNewTrip();
};

#endif //EX2_DRIVER_H
