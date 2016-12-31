#include "Driver.h"
#include "sockets/Udp.h"
#include "sockets/Udp.h"
#include <unistd.h>
#include <iostream>



Driver::Driver() {
    this->driverId=0;
    this->age=0;
    this->maritalStatus='c';
    this->vehicleId=0;
    this->exp=0;
}

/*Driver::Driver(int driverId, int age, char mStatus, int exp, int vehicleId, Graph* map) {
    numberOfcustomers=0;
    this->driverId=driverId;
    this->age=age;
    this->maritalStatus=mStatus;
    this->vehicleId=vehicleId;
    this->exp = exp;
    this->gps = map;
}*/

Driver::Driver(int driverId, int age, char mStatus, int exp, int vehicleId) {
    //numberOfcustomers=0;
    this->driverId=driverId;
    this->age=age;
    this->maritalStatus=mStatus;
    this->exp=exp;
    this->vehicleId=vehicleId;
}

/*
* using its grid, the driver uses a bfs algorithms to
* continue travelling until it arrives at its destination.
*/
Trip Driver::drive() {
    cout << "IN DRIVE OF DRIVER"<< endl;
    BFS bfs = BFS(gps);
    cout << "DRIVER INFO:"<<endl << this->driverId;
    cout << "TRIP ID:" << myTrip.getId()<<endl;
    cout << endl<< myTrip.getStart()->getX();
    Coordinate* start = myTrip.getStart();
    cout << "START X: " << myTrip.getStart()->getX() << endl;
    Coordinate* end = myTrip.getEnd();
    cout << "START X: " << end->getX() << endl;
    cout << "start y: "<<  start->getX() << endl;
    Coordinate* c;

        c  = bfs.getNextInPath(start, end);
        myTrip.updateStartPoint(c);
    gps->resetGraph();
    return myTrip;
}

int Driver::getAge() {
    return age;
}

int Driver::getDriverId() {
    return driverId;
}

double Driver::getSatisfaction() {
    return avgSatisfaction;
}

Taxi Driver::getTaxi() {
    return taxi;
}

Trip Driver::getTrip() {
    return myTrip;
}

vector<Passenger> Driver::getPassengers() {
    return myPassengers;
}

char Driver::getMaritalStatus() {
    return maritalStatus;
}

void Driver::setTaxi(Taxi t) {
    taxi =t;
}

void Driver::setTrip(Trip t) {
    cout << "IN SET TRIP: id =  " << t.getId()<<endl;
//    cout << "start x =  "<< t.getEnd()->getX()<<endl;
    myTrip = t;
}

/*
* adds another rating and calculates average.
*/
void Driver::rateMe(int rating) {
    numberOfcustomers=+1;
    totalRate+=rating;
    avgSatisfaction =totalRate/numberOfcustomers;
}

void Driver::addPassenger(Passenger p) {
    myPassengers.push_back(p);
}

Driver::~Driver() {

}

int Driver::getVehicleId() {
     return vehicleId;
}

bool Driver::arrived() {
    if(myTrip.getStart()->equalTo(myTrip.getEnd())) {
        return true;
    }
    return false;
}

void Driver::setMap(Graph* map) {
    gps = map;
}