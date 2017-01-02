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
    this->myTrip = new Trip();
}

/*
* using its grid, the driver uses a bfs algorithms to
* continue travelling until it arrives at its destination.
*/
Trip* Driver::drive() {
    cout << "IN DRIVE OF DRIVER"<< endl;
    cout <<endl;
    BFS bfs = BFS(gps);
    cout << "INFO IN SERVER DRIVE OF DRIVER:" << endl;
    cout << "DRIVER INFO: "<<endl;
    cout << "ID: " << this->getDriverId()<<endl;
    cout << "START OF TRIP: " << this->getTrip()->getStartX() << "," << this->getTrip()->getStartY()<<endl;
    cout << "END OF TRIP: " << this->getTrip()->getEndX() << "," << this->getTrip()->getEndY()<<endl;
    Coordinate* start;
    int x = myTrip->getStartX();
    int y = myTrip->getStartY();
    start = new Point(x, y);
    Coordinate* end;
    x = myTrip->getEndX();
    cout << "END X: "<< x << endl;
    y = myTrip->getEndY();
    cout << "END Y: "<< y << endl;
    end = new Point(x, y);
    Coordinate* c;
    c  = bfs.getNextInPath(start, end);
    cout << "** AFTER GET NEXT IN PATH" << endl;
    Trip* newTrip = new Trip(myTrip->getId(), c->getCoordinates()[0], c->getCoordinates()[1], myTrip->getEndX(), myTrip->getEndY(),1,20,0);
    //myTrip->updateStartPoint(c);
    delete start;
    delete end;
    cout << "NEWTRIP: "<<newTrip->getStartX() << "," << newTrip->getStartY() << endl;

    myTrip = newTrip;
    cout << "MyTrip: " << myTrip->getStartX() << "," << myTrip->getStartY()<< endl;
    cout << "** AFTER UPDATING START POINT OF DRIVER ** " << endl;
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

Trip* Driver::getTrip() {
    return myTrip;
}

vector<Passenger> Driver::getPassengers() {
    return myPassengers;
}

char Driver::getMaritalStatus() {
    return maritalStatus;
}

void Driver::setTaxi(Taxi t) {
    taxi = t;
}

void Driver::setTrip(Trip* t) {
    delete myTrip;
    myTrip = new Trip(t);
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
    if (myTrip->getStartX() == myTrip->getEndX()) {
        if(myTrip->getStartY() == myTrip->getEndY()) {
            //this->needNewTrip();
            return true;
        }
    }
    return false;
}


void Driver::setMap(Graph* map) {
    gps = map;
}

void Driver::needNewTrip() {
    //myTrip = new Trip();
}