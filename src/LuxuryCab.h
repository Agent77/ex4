//
// Created by nirbs on 14/12/16.
//

#ifndef TRY_LUXURYCAB_H
#define TRY_LUXURYCAB_H

#include "Taxi.h"

class LuxuryCab: public Taxi {
    friend class boost::serialization::access;

    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {

    }
public:
    LuxuryCab(int id, char type, char c){};

    void updateKms(){};
    int getSpeed(){};
    void getManu(){};
    int getTariff(){};
    int getId() {};
    int getKms(){};
};



#endif //TRY_LUXURYCAB_H
