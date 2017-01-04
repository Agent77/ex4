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
    vector<Driver> waitingDrivers;
    vector<Taxi> vehicles;
    int portNum;
public:
    Server();
    void run();
    void initialize();
    Trip getTripFromClient();
    void SendTripToClient();
    int createClients(string port);
    void assignVehicleToClient();
    void receiveDriver();
    string createString(char* buffer, int bufferSize);
    void sendCommand(int command);
    void sendNextLocation();
    void closeSockets();


};


#endif //EX2_GAMEFLOW_H
