
#ifndef GTESTEX3_TAXI_H
#define GTESTEX3_TAXI_H

#include <string>
#include "BFS.h"

class Taxi {
protected:
    BFS* gps;
    int cabId;
    int kmPassed;
    char manufacturer;
    char color;
    int tariff;
    int speed;

public:
    Taxi();
    Taxi(int id, char type, char c);
    ~Taxi(){};
    virtual void updateKms();
    virtual int getSpeed();
    virtual void getManu();
    virtual int getTariff();
    virtual int getId();
    virtual int getKms();
};


#endif //EX2_TAXI_H
