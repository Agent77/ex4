#ifndef EX1_COORDINATE_H
#define EX1_COORDINATE_H

#include <iostream>
/*
 * Abstract class to represent an objects location,
 * based on any number of coordinates given, using an
 * array of locations (x,y,z,etc...). This allows
 * us to handle any dimension wanted by the user.
 */
using namespace std;
class Coordinate {
public:
    Coordinate(){};
    Coordinate(Coordinate* p);
    Coordinate(int* a);
    ~Coordinate(){};
    virtual int* getCoordinates(){};
    virtual int getX(){};
    virtual int getY(){};
    virtual int getNextCoordinate(int place);
    friend std:: ostream& operator<<(std :: ostream& out, Coordinate& t);
    virtual void printFormat(ostream& o) =0;
    virtual bool equalTo(Coordinate* c) {};
    virtual Coordinate* getMyLocation(){};
protected:
    int locs[10];
};
#endif //EX1_COORDINATE_H