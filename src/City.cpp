#include "City.h"
#include "StandardCab.h"
#include "LuxuryCab.h"


City::City() {

}

void City::CallTaxiCenter(Passenger p) {

}
Passenger City::checkForPassengerCalls() {

}


Driver City::createDriver(string s) {
    int info[6];
    char status;
    int f;
    int i = 0;
    string g;
    std::istringstream sep(s);
    std::getline(sep, g,',');
    std::istringstream (g)>>f;
    for (int j=0; j<s.size()/2;j++){
        if (i!=2){
            std::istringstream (g)>>f;
            info[i]= f;
        } else{
            status=g[0];
        }
        std::getline(sep, g,',');
        i++;
    }
    Driver d = Driver(info[0], info[1], status, info[3], info[4]);
    return d;
}


Trip City::createTrip(string s) {
    //7 ints
    int i = 0;
    int value[13];
    int f;
    string g;
    std::istringstream sep(s);
    std::getline(sep, g,',');
    std::istringstream (g)>>f;
    for (int j=0; j<s.size()/2;j++) {
        value[i] = f;
        i++;
        std::getline(sep, g,',');
        std::istringstream (g)>>f;
    }
    Trip trip = Trip(value[0],value[1], value[2], value[3],
                     value[4], value[5], value[6]);
    return trip;
}

Coordinate* City::createCoordinate(string s) {
    int x = (int)s[0] - 48;
    int y = (int)s[2] - 48;
    Coordinate* point = new Point(x, y);
    return point;
}

Graph* City::createGraph(string s, string s1) {
    int x = (int)s[0] - 48;
    int y = (int)s1[0] - 48;
    Graph *graphPointer = new Grid(x, y);
    return graphPointer;
}

Taxi City::createTaxi(string s) {
    int id = (int)s[0] - 48;
    int type = (int)s[2] - 48;
    if(type == 1) {
        StandardCab t = StandardCab(id, s[4], s[6]);
        return t;
    } else {
        LuxuryCab t = LuxuryCab(id, s[4], s[6]);
        return t;
    }
}