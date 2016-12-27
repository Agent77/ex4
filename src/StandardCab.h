//
// Created by nirbs on 14/12/16.
//

#ifndef TRY_STANDARDCAB_H
#define TRY_STANDARDCAB_H


#include "Taxi.h"

class StandardCab: public Taxi {
    friend class boost::serialization::access;

    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {

    }
public:
    StandardCab() {};
    StandardCab(int id, char type, char c) :Taxi(id,type,c) {

    }
    //~Taxi(){};
    void updateKms(){};
    int getSpeed(){};
    void getManu(){};
    int getTariff(){};
    int getId() {};
    int getKms(){};
};


#endif //TRY_STANDARDCAB_H
