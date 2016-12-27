
#include "Trip.h"

Trip::Trip() {

}
//c
Trip::Trip(int tripId, int xStart, int yStart, int xEnd, int yEnd, int numOfPassengers, double tariff, int time) {
    this->tripId=tripId;
    this->xStart=xStart;
    this->yStart=yStart;
    this->xEnd=xEnd;
    this->yEnd=yEnd;
    this->start = new Point(xStart, yStart);
    this->end = new Point(xEnd, yEnd);
    this->numOfPassengers=numOfPassengers;
    this->tariff = tariff;
    this->startTime = time;
}

Trip::~Trip() {

}

int Trip::getId() {
    return tripId;
}

int Trip::getMeters() {
    return metersPassed;
}

int Trip::getNumOfPassengers() {
    return numOfPassengers;
}

double Trip::getTariff() {
    return tariff;
}
Coordinate* Trip::getStart() {
    return start;
}
Coordinate* Trip::getEnd() {
    return end;
}

void Trip::addMeters() {
    metersPassed =+1;
}

/*
* each time the driver moves, the start point of its trip is updated.
*/
void Trip::updateStartPoint(Coordinate *c){
    xStart = c->getNextCoordinate(0);
    yStart = c->getNextCoordinate(1);
    start = new Point(xStart, yStart);
}

int Trip::getTripTime() {
    return startTime;
}