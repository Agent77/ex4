

#ifndef EX1_POINT_H
#define EX1_POINT_H
#include <iostream>
#include "Coordinate.h"
/*
 * Point class is a specific implementation of
 * the Coordinate abstract class. It has an array of size
 * 2, for x and y, so is used for 2D graphs.
 */
class Point: public Coordinate {
protected:
    int locs[2];
public:
    Point();
    ~Point();
    Point(int xAxis, int yAxis);
    void printFormat(ostream& o);
    bool equalTo(Coordinate* c);
    friend bool operator== (Point const& p, Point const& p2);
    int getX();
    int* getCoordinates();
    Point(Coordinate* cor);
    int getY();
    int getNextCoordinate(int place);
    Coordinate* getMyLocation();
};
#endif //EXONE_POINT_H