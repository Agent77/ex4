
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

int main(int argc, char* argv[]) {

    Server server = Server();

    // INITIALIZES MAP
    server.initialize();

    // OPENS SOCKET FOR ONE CLIENT
    server.createClients(atoi(argv[1]));

    // RUNS SWITCH CASE
    server.run();
    server.closeSockets();
    return 0;
}

Server::Server() {
    clock = Clock();
}

void Server::closeSockets() {
    tc.~TaxiCenter();
    socket->~Socket();
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
    std::istringstream(obstacles) >> obstacleCount;
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


void Server::SendTripToClient() {

    std::string serializedTrip;
    int counter=0;
    Trip trip;
    int numOfTrips=tc.checkTripTimes(clock.getTime());
    // SEND TRIP TO CLIENT
    for (int i = 0; i < numOfTrips; i++) {
        trip  = tc.getNextTrip(clock.getTime());
        Driver d =  waitingDrivers.front();
        waitingDrivers.erase(waitingDrivers.begin());//TODO HERE SEGMENTATION FAULT
        d.setTrip(&trip);
        d.setMap(tc.getMap());
        tc.addDriver(d);
        tc.updateDriverTrip(trip);
        Trip* trip1 = &trip;
        boost::iostreams::back_insert_device<std::string> inserter(serializedTrip);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << trip1;
        s.flush();
        Server::sendCommand(2);
        socket->sendData(serializedTrip);
    }
}

int Server::createClients(int portNum) {

    // creates port for clients
    socket = new Udp(1, portNum);

    //creates new socket for single client
    int result = socket->initialize();

}
string Server::createString(char* buffer, int bufferSize) {
    std::string s(buffer, bufferSize);
    return s;

}
void Server::receiveDriver() {

    // RECEIVE DRIVER FROM CLIENT
    char buffer[1024];
    socket->reciveData(buffer, sizeof(buffer));

    // DESERIALIZE BUFFER INTO DRIVER
    string s = createString(buffer, sizeof(buffer));
    Driver *receivedDriver;
    boost::iostreams::basic_array_source<char> device(s.c_str(), s.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> receivedDriver;
    waitingDrivers.push_back(*receivedDriver);
    delete receivedDriver;

}

void Server::sendCommand(int command) {

    // SERIALIZATION OF TAXI
    std::string commandString;
    boost::iostreams::back_insert_device<std::string> inserter(commandString);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
    boost::archive::binary_oarchive oa(s1);
    oa << command;
    s1.flush();
    socket->sendData(commandString);
}

void Server::sendNextLocation() {

    int x = 0;
    int y = 0;
    if(tc.getDrivers().size() > 0) {

        for(int i=0; i<tc.getDrivers().size() && tc.getDrivers()[i].getTrip()->getTripTime()<clock.getTime()+1; i++) {
            Trip* t = tc.getDrivers()[i].drive();
            tc.updateDriverTrip(t, i);
             x = t->getStartX();
             y = t->getStartY();
            Point* ptrPoint = new Point(x, y);

            std::string nextLocation;
            boost::iostreams::back_insert_device<std::string> inserter(nextLocation);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
            boost::archive::binary_oarchive oa(s1);
            oa << ptrPoint;
            s1.flush();
            Server::sendCommand(9);
            socket->sendData(nextLocation);
            delete ptrPoint;
            if(tc.getDrivers()[i].arrived()) {
                waitingDrivers.push_back(tc.getDrivers()[i]);
                tc.deleteDriver(i);
                Server::SendTripToClient();
            }
        }
    }
}

void Server::assignVehicleToClient() {
    // FINDS CORRECT TAXI FOR DRIVER ID
    int counter = 0;
    vector<Taxi*>::iterator taxiIter = vehicles.begin();


    int id = waitingDrivers.front().getDriverId();

    while ((*(taxiIter))->getId() != id && taxiIter!= vehicles.end()){
        taxiIter++;
        counter++;

    }

    waitingDrivers.front().setTaxi((*(*taxiIter))); //still in vector because needs a trip before adding to taxi center

    Taxi* taxiPointer = (*(taxiIter));
    // SERIALIZATION OF TAXI
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
    boost::archive::binary_oarchive oa(s1);
    oa << taxiPointer;
    s1.flush();
    // RETURN TAXI TO CLIENT
    socket->sendData(serial_str);

    vehicles.erase(vehicles.begin() + counter);

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
                // ASSIGNS A VEHICLE TO CLIENT ONLY IF TRIP TIME ARRIVES
                Server::receiveDriver();
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
                vehicles.push_back(&t);
                break;
            }
            case 4: {
                cin >> driverId;
                tc.requestDriverLocation(driverId);
                break;
            }
            case 9:
                // ADVANCE TIME
                clock.increaseTime();
                Server::SendTripToClient();
                Server::sendNextLocation();


                break;
            case 7:
            Server::sendCommand(7);
                run = 0;
                break;
            default:
                break;
        }
    }
}

