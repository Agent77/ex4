
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

    Server server = Server();

    // INITIALIZES MAP
    server.initialize();

    cout<<"server initialized"<<endl;

    // OPENS SOCKET FOR ONE CLIENT
    server.createClients(1);

    cout<<"sockect created"<<endl;

    // RUNS SWITCH CASE
    server.run();

    return 0;
}

Server::Server() {
    clock = Clock();
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

    cout<<"grid created"<<endl;

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
    cout << "IN SEND TRIP TO CLIENT" << endl;
    std::string serializedTrip;
    int counter=0;
    Trip trip;
    int numOfTrips=tc.checkTripTimes(clock.getTime());
    // SEND TRIP TO CLIENT
    for (int i = 0; i < numOfTrips; i++) {
        trip  = tc.getNextTrip(clock.getTime());
        cout << "** START OF TRIP FROM GETNEXTTRIP:** " << trip.getStartX() << "," << trip.getStartY()<<endl;
        cout << "** END OF TRIP FROM GETNEXTTRIP ** : " << trip.getEndX() << "," << trip.getEndY()<<endl;
        Driver d =  waitingDrivers.front();
        waitingDrivers.erase(waitingDrivers.begin());
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
        socket->sendData(serializedTrip);
        Server::sendCommand();
    }



    //cout << "ID: " << currentDriver.getDriverId()<<endl;
    //cout << "START OF TRIP: " << currentDriver.getTrip()->getStartX() << "," << currentDriver.getTrip()->getStartY()<<endl;
   // cout << "END OF TRIP: " << currentDriver.getTrip()->getEndX() << "," << currentDriver.getTrip()->getEndY()<<endl;
    //vector<Driver> drivers = tc.getDrivers();
    //vector<Driver>::iterator drIter = drivers.begin();

    /*while((*(drIter)).getDriverId() != currentDriver.getDriverId()) {
        drIter++;
        counter++;
        Trip* trip1 =
    boost::iostreams::back_insert_device<std::string> inserter(serializedTrip);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << trip1;
    s.flush();
    socket->sendData(serializedTrip);
    }*/

   // tc.getDrivers().at(counter).setTrip(&trip); //TODO SET HERE DOES NOT WORK OR IT DOES AND LOSES IT IN DRIVE()
    //(*(drIter)).setTrip(&trip);
    //tc.resetDrivers(drivers);



    cout <<endl;

}

int Server::createClients(int amountOfDrivers) {

    // creates port for clients
    socket = new Udp(1, 5555);

    //creates new socket for single client
    int result = socket->initialize();

}
string Server::createString(char* buffer, int bufferSize) {
    std::string s(buffer, bufferSize);
    return s;

}
void Server::receiveDriver() { //TODO CHECK CLOCK
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



}

void Server::sendCommand() {
    int s = 9;
    // SERIALIZATION OF TAXI
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
    boost::archive::binary_oarchive oa(s1);
    oa << s;
    s1.flush();
    socket->sendData(serial_str);
}

void Server::sendNextLocation() {
    int x = 0;
    int y = 0;
    cout << " ** IN SEND NEXT LOCATION ** " << endl;

    if(tc.getDrivers().size() > 0) {
        vector<Driver>::iterator driverIter = tc.getDrivers().begin();
        while(driverIter != tc.getDrivers().end()) {
            Trip* t = (*(driverIter)).drive();
             x = t->getStartX();
             y = t->getStartY();
            Point* ptrPoint = new Point(x, y);
            if((*(driverIter)).arrived()) {
                waitingDrivers.push_back((*(driverIter)));
                Server::SendTripToClient();
            }
            std::string nextLocation;
            boost::iostreams::back_insert_device<std::string> inserter(nextLocation);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter);
            boost::archive::binary_oarchive oa(s1);
            oa << ptrPoint;
            s1.flush();
            socket->sendData(nextLocation);
            delete ptrPoint;
        }
    }
}

void Server::assignVehicleToClient() {
    cout << "** IN ASSIGN VEHICLE **" << endl;
    // FINDS CORRECT TAXI FOR DRIVER ID
    int counter = 0;
    vector<Taxi*>::iterator taxiIter = vehicles.begin();
    int id = ((waitingDrivers)).front().getDriverId(); //TODO FRONT OR BACK?
    while ((*(taxiIter))->getId() != id){
        taxiIter++;
        counter++;
    }
    waitingDrivers.front().setTaxi((*(*taxiIter))); //still in vector because needs a trip before adding to taxi center
    Taxi* taxiPointer = (*(taxiIter));
    vehicles.erase(vehicles.begin() + counter);
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
            case 9: {
                        Server::SendTripToClient();
                        Server::sendNextLocation();

                    }
                // ADVANCE TIME
                clock.increaseTime();
                // SEND A NEW TRIP TO DRIVER, and DELETE THAT TRIP FROM LIST AND UPDATE DRIVER'S TRIP
                break;
            case 7:
                run = 0;
                break;
            default:
                break;
        }
    }
}

