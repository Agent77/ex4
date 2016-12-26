#include "Passenger.h"
#include <cstdlib>

Passenger::Passenger(Point p, Point p2) {
    source = p;
    dest = p2;
}

int Passenger::rateDriver() {
    int rate = rand() %5;
    return rate;
}

Point Passenger::getSource() {
    return source;
}

Point Passenger::getDestination() {
    return dest;
}