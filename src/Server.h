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
#include "Clock.h"

using namespace std;
using namespace boost::archive;
#ifndef EX2_GAMEFLOW_H
#define EX2_GAMEFLOW_H


class Server {

private:
    Socket* socket;
    City city;
    TaxiCenter tc;
    Clock clock;
    Driver currentDriver;
public:
    Server();
    void run();
    void initialize();
    Trip getTripFromClient();
    void SendTripToClient();
    int createClients(int amountOfDrivers);
    void assignVehicleToClient();
    void receiveDriver();


};


#endif //EX2_GAMEFLOW_H
