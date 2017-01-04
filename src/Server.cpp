/************************************************************
* File description: Server class  file.     				*
* Acts as server, receives clients, and controls the game
* flow of input/out, and serialization                      *
************************************************************/
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
/***********************************************************************
	* function name: main										       *
	* The Input: port number										   *
	* The output: none										           *
	* The Function operation: calls neccessary functions to run server *
	***********************************************************************/
int main(int argc, char* argv[]) {

    Server server = Server();

    // INITIALIZES MAP/GRID
    server.initialize();

    string s= argv[1];
    // OPENS SOCKET FOR ONE CLIENT
    server.createClients(s);

    // RUNS SWITCH CASE
    server.run();

    //CLOSES SOCKETS
    server.closeSockets();
    return 0;
}

Server::Server() {
    clock = Clock();
}

/***********************************************************************
	* function name: closeSockets										   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: notifies all clients to close themselves     *
	***********************************************************************/
void Server::closeSockets() {//TODO NEXT DELETE
    tc.~TaxiCenter();
    waitingDrivers.clear();
    waitingDrivers.swap(waitingDrivers);
    vehicles.clear();
    vehicles.swap(vehicles);
    //g->deleteGraph();
    delete g;
    delete socket;
}

/**************************************************************************
	* function name: initialize											   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: initializes the grid and obstacles for the
     * game                                                                *
****************************************************************************/
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
    //Adds obstacles at given points in grid
    if (obstacleCount != 0) {
        string obstacle;
        for (int count = 0; count < obstacleCount; count++) {
            cin >> obstacle;
            Coordinate* c = city.createCoordinate(obstacle);
            grid->addObstacle(c);
        }
    }
    //adds grid to the taxi center
    tc = TaxiCenter(grid);
    g = grid;
}

/***********************************************************************
	* function name: SendTripToClient								       *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: Finds the correct trip according to the      *
     * current time, serializes it, and send it to the client              *
	***********************************************************************/
void Server::SendTripToClient() {
    std::string serializedTrip;
    int counter=0;
    Trip trip;

    //Finds how many trips start at the current time
    int numOfTrips=tc.checkTripTimes(clock.getTime());

    // SEND TRIP TO EACH CLIENT
    for (int i = 0; i < numOfTrips; i++) {
        //gets trip that starts at current time
        trip  = tc.getNextTrip(clock.getTime());
        //gets next driver
        Driver d =  waitingDrivers.front();
        //erases from temporary vector of drivers without trips
        waitingDrivers.erase(waitingDrivers.begin());
        d.setTrip(&trip);
        d.setMap(tc.getMap());
        tc.addDriver(d);
        Trip* trip1 = &trip;
        //SERIALIZATION OF TRIP
        boost::iostreams::back_insert_device<std::string> inserter(serializedTrip);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << trip1;
        s.flush();
        //Notifies client that they are going to receive a trip now
        Server::sendCommand(2);
        socket->sendData(serializedTrip);
    }
}

/***********************************************************************
	* function name: createClients										   *
	* The Input: string of port number													   *
	* The output: none										               *
	* The Function operation: opens a socket for the client to reach	   *
	***********************************************************************/
int Server::createClients(string port) {
    portNum=stoi(port);

    // creates port for clients
    socket = new Udp(1, portNum);

    //creates new socket for single client
    int result = socket->initialize();

}

/***********************************************************************
	* function name: createString									       *
	* The Input: buffer and size of buffer													   *
	* The output: none										               *
	* The Function operation: creates a string from the buffer	           *
	***********************************************************************/
string Server::createString(char* buffer, int bufferSize) {
    std::string s(buffer, bufferSize);
    return s;
}

/***********************************************************************
	* function name: receiveDriver										   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: waits to receive serialized version of driver
     * sent from client and adds it to a vector of temporary drivers       *
	***********************************************************************/
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
    //adds received driver to temp vector of drivers, until it is assigned a trip
    waitingDrivers.push_back(*receivedDriver);
    delete receivedDriver;
}

/***********************************************************************
   * function name: sendCommand										   *
   * The Input: int													   *
   * The output: none										               *
   * The Function operation: serializes and sends a command to client
    * Sends a number, depending on whether it wants the client to wait for
    * a trip, a new location, or a vehicle, or to close itself            *
   ***********************************************************************/
void Server::sendCommand(int command) {

    // SERIALIZATION OF COMMAND
    std::string commandString;
    boost::iostreams::back_insert_device<std::string> inserter(commandString);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
    boost::archive::binary_oarchive oa(s1);
    oa << command;
    s1.flush();
    socket->sendData(commandString);
}

/***********************************************************************
	* function name: sendNextLocation									   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: drives the drivers, gets its next location,
     * serializes the point and sends it to client                         *
	***********************************************************************/
void Server::sendNextLocation() {

    int x = 0;
    int y = 0;
    if(tc.getDrivers().size() > 0) {
        //Drives all drivers and sends next locations to clients
        for(int i=0; i<tc.getDrivers().size() && tc.getDrivers()[i].getTrip()->getTripTime()<clock.getTime(); i++) {
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
            //notifies clients they are about to receive a new location
            Server::sendCommand(9);
            socket->sendData(nextLocation);
            delete ptrPoint;
            //need to assign driver a new trip
            if(tc.getDrivers()[i].arrived()) {
                //re-adds driver to waiting drivers
                waitingDrivers.push_back(tc.getDrivers()[i]);
                //delets drivers without trips from taxi center
                tc.deleteDriver(i);
                Server::SendTripToClient();
            }
        }
    }
}

/***********************************************************************
	* function name: assignVehicleToClient												   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: finds the right vehicle depending on driver
     * id, serializes it, and sends it to the client                       *
	***********************************************************************/
void Server::assignVehicleToClient() {
    int counter = 0;
    vector<Taxi>::iterator taxiIter = vehicles.begin();
    int id = waitingDrivers.front().getDriverId();

    // FINDS CORRECT TAXI FOR DRIVER ID
    while ((*(taxiIter)).getId()!= id && taxiIter!= vehicles.end()){
        taxiIter++;
        counter++;
    }
    //sets taxi to driver with matching id, who still doesnt have a trip
    waitingDrivers.front().setTaxi((*taxiIter));

    Taxi* taxiPointer = &(*(taxiIter));
    // SERIALIZATION OF TAXI
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
    boost::archive::binary_oarchive oa(s1);
    oa << taxiPointer;
    s1.flush();
    // RETURN TAXI TO CLIENT
    socket->sendData(serial_str);
    //once taxi has been assigned to a driver, it can be deleted from vehicle vector
    vehicles.erase(vehicles.begin() + counter);

}

/***********************************************************************
   * function name: run												   *
   * The Input: none												   *
   * The output: none										           *
   * The Function operation: contains switch case which runs the main
   * flow of the input and client/server interactions                  *
   ********************************************************************/
void Server::run() {
    int run = 1;
    char action1;
    int driverId;
    string input;
    string s;
    const int insertDriver = 1;
    const int insertTrip = 2;
    const int insertVehicle = 3;
    const int requestDriverId = 4;
    const int moveDrivers = 9;
    const int close = 7;

//Actions the user can perform
    while (run) {
        cin >> action1;
        int action = (int)action1 - 48;
        switch(action) {
            case insertDriver: //Insert Driver
            {
                cin >> input; //how many drivers
                // ASSIGNS A VEHICLE TO CLIENT ONLY IF TRIP TIME ARRIVES
                Server::receiveDriver();
                Server::assignVehicleToClient();
                break;
            }
            case insertTrip: {
                cin >> input;
                Trip t = city.createTrip(input);
                tc.addTrip(t);
                break;
            }
            case insertVehicle: {
                cin >> s;
                Taxi t = city.createTaxi(s);
                tc.addTaxi(t);
                vehicles.push_back(t);
                break;
            }
            case requestDriverId: {
                cin >> driverId;
                tc.requestDriverLocation(driverId);
                break;
            }
            case moveDrivers:
                // ADVANCE TIME
                clock.increaseTime();
                Server::SendTripToClient();
                Server::sendNextLocation();
                break;
            case close:
                Server::sendCommand(7);
                run = 0;
                break;
            default:
                break;
        }
    }
}