
#ifndef GTESTEX3_TAXI_H
#define GTESTEX3_TAXI_H

#include <string>
#include "BFS.h"

class Taxi {
    friend class boost::serialization::access;

    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {
        ar & gps;
        ar & cabId;
        ar & kmPassed;
        ar & manufacturer;
        ar & color;
        ar & tariff;
        ar & speed;
    }
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
