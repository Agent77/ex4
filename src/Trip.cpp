
#include "Trip.h"

Trip::Trip() {
    xStart = 0;
    yStart = 0;
    yEnd = 0;
    xEnd = 0;
    startTime = 0;
    tripId = 0;
}

/*
 * non-default constructor
 */
Trip::Trip(int tripId, int xStart, int yStart, int xEnd, int yEnd, int numOfPassengers, double tariff, int time) {
    this->tripId=tripId;
    this->xStart=xStart;
    this->yStart=yStart;
    this->xEnd=xEnd;
    this->yEnd=yEnd;
    this->start =   Point(xStart, yStart);
    this->end =   Point(xEnd, yEnd);
    this->numOfPassengers=numOfPassengers;
    this->tariff = tariff;
    this->startTime = time;
}

/*
 * copy constructor for Trip.
 */
Trip::Trip(Trip* t) {
  this->tripId = t->getId();
  this-> xStart = t->getStartX();
  this-> xEnd = t->getEndX();
   this-> yStart = t->getStartY();
   this->yEnd = t->getEndY();
    this->startTime = t->getTripTime();


}

Trip::~Trip() {

}

int Trip::getStartX() {
     return xStart;
}
 int Trip::getStartY() {
     return yStart;
 }

int Trip::getEndX() {
    return xEnd;
}

int Trip::getEndY() {
     return yEnd;
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

Point Trip::getStart() {
    return start;
}
Point Trip::getEnd() {
    return end;
}

void Trip::addMeters() {
    metersPassed =+1;
}

/*
* each time the driver moves, the start point of its trip is updated.
*/
void Trip::updateStartPoint(Point p){
    xStart = p.getCoordinates()[0];
    yStart = p.getCoordinates()[1];
}

int Trip::getTripTime() {
    return startTime;
}