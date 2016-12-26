//
// Created by Tiki Lobel on 11/29/16.
//

#ifndef EX2_CITY_H
#define EX2_CITY_H
#include "TaxiCenter.h"
#include "Passenger.h"
#include "BFS.h"
#include <boost/lexical_cast.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class City {
private:
    TaxiCenter tc;
public:
    City();
    void CallTaxiCenter(Passenger p);
    Passenger checkForPassengerCalls();
    TaxiCenter getTaxiCenter() {};
    Driver createDriver(string s);
    Trip createTrip(string s);
    Graph* createGraph(string s, string s1);
    Taxi createTaxi(string s);
    Coordinate* createCoordinate(string obstacleLocation);
};


#endif //EX2_CITY_H
