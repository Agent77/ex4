#include <sstream>
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/access.hpp>
#include "City.h"
#include "Driver.h"
#include "Trip.h"
#include "Graph.h"
#include "Coordinate.h"
#include "TaxiCenter.h"
#include "sockets/Socket.h"
using namespace std;
using namespace boost::archive;
std::stringstream ss;
#ifndef EX2_GAMEFLOW_H
#define EX2_GAMEFLOW_H


class Server {

private:
    Socket* socket;
    City city;
    TaxiCenter tc;
public:
    Server() {};
    //void doOneFrame();
    void run();
    void initialize();
    Trip getTripFromClient();
    void SendTripToClient();
    int createClients(int amountOfDrivers);
    void assignVehicleToClient();


};


#endif //EX2_GAMEFLOW_H
