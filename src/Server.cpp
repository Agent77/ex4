
#include "Server.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Point.h"
#include "BFS.h"
#include "Driver.h"
#include "City.h"
#include "TaxiCenter.h"
//#include <boost/lexical_cast.hpp>
//#include <boost/tokenizer.hpp>
#include "Server.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "sockets/Udp.h"

using namespace std;

int main() {

    Server gf = Server();

    // Gets initial information before server/client interaction,
    // along with switch case in run()
    gf.initialize();
    gf.createClients(1);

    // Creates new socket for new drivers
    gf.assignVehicleToClient();

    // Begin to move based on input
    gf.run();
    return 0;
}
/*
* Initializes the grid and taxi center.
*/
void Server::initialize() {
    string obstacles;
    string size1;
    string size2;
    int obstacleCount;

    //To be used later as graph size
    cin >> size1;
    cin >> size2;
    Graph *grid = city.createGraph(size1, size2);

    //Checks for obstacles
    cin >> obstacles;
    //std::istringstream(obstacles) >> obstacleCount;
    //int obstacleCount ;//= atoi(obstacles);
    if (obstacleCount != 0) {
        string obstacle;
        for (int count = 0; count < obstacleCount; count++) {
            cin >> obstacle;
            Coordinate* c = city.createCoordinate(obstacle);
            grid->addObstacle(c);
        }
    }
    tc = TaxiCenter(grid);
}
Trip Server::getTripFromClient() {
    char buffer[1024];

    // RECEIVE TRIP FROM CLIENT
    socket->reciveData(buffer, sizeof(buffer));

    // DESERIALIZE BUFFER INTO TRIP
    string s = buffer;
    Trip *trip;
    boost::iostreams::basic_array_source<char> device(s.c_str(), s.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> trip;

    return *trip;

}

void Server::SendTripToClient() {

    string serializedTrip;
    // SEND TRIP TO CLIENT
    Trip trip = tc.getNextTrip();
    boost::iostreams::back_insert_device<std::string> inserter(serializedTrip);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << trip;
    s.flush();
    socket->sendData(serializedTrip);
}

int Server::createClients(int amountOfDrivers) {

    // creates port for clients
    socket = new Udp(1, 5555);

    //creates new socket for single client
    int result = socket->initialize();

}
void Server::assignVehicleToClient() {
    // RECEIVE DRIVER FROM CLIENT
    char buffer[1024];
    socket->reciveData(buffer, sizeof(buffer));

    // DESERIALIZE BUFFER INTO DRIVER
    string s = buffer;
    Driver *receivedDriver;
    boost::iostreams::basic_array_source<char> device(s.c_str(), s.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> receivedDriver;

    // ADDS DRIVER TO TAXI CENTER
    tc.addDriver(*receivedDriver);

    // FINDS CORRECT TAXI FOR DRIVER ID
    Taxi t = tc.assignTaxi(receivedDriver->getDriverId());
    Taxi* taxiPointer = &t;

    // SERIALIZATION OF TAXI
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
    boost::archive::binary_oarchive oa(s1);
    oa << taxiPointer;
    s1.flush();

    // RETURN TAXI TO CLIENT
    socket->sendData(serial_str);
}
/*
* runs the switch case so the user can constantly 
* add input.
*/
void Server::run() {
    int run = 1;
    char action1;
    int driverId;
    string input;
    string s;

//Actions the user can perform
    while (run) {
        cin >> action1;
        int action = (int)action1 - 48;
        switch(action) {
            case 1: //Insert Driver
            {
                cin >> input; //how many drivers
                Server::assignVehicleToClient();
                break;
            }
            case 2: {
                cin >> input;
                Trip t = city.createTrip(input);
                tc.addTrip(t);
                break;
            }
            case 3: {
                cin >> s;
                Taxi t = city.createTaxi(s);
                tc.addTaxi(t);
                break;
            }
            case 4: {
                cin >> driverId;
                tc.requestDriverLocation(driverId);
                break;
            }
            case 9: {
                // ADVANCE TIME

                //SEND 9 TO ALL CLIENTS
                socket->sendData("9");

                //RECEIVE TRIP FROM CLIENT
                Trip t = Server::getTripFromClient();

                // CHECK IF AT DESTINATION, IF IT IS:
                // SEND A NEW TRIP TO DRIVER, and DELETE THAT TRIP FROM LIST AND UPDATE DRIVER'S TRIP

                // UPDATE CORRECT DRIVER'S TRIP
                tc.updateDriverTrip(t);
                break;
            }
            case 7:
                run = 0;
                break;
            default:
                break;
        }
    }
}

