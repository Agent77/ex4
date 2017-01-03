#include "sockets/Udp.h"
#include "Driver.h"
#include "DriverClient.h"
#include "LuxuryCab.h"
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
//typedef enum commands{NEWTRIP = 2, NEWPOINT = 9, CLOSE = 7};
using namespace std;
using namespace boost::archive;
int main() {
    City c = City();

    string d;
    cin >> d;
    Driver dr = c.createDriver(d);
    Driver* driver = &dr;

    DriverClient client = DriverClient();

    client.openSocket(driver);
    client.receiveVehicle();
    client.receiveCommand();
    return 0;
}
DriverClient::DriverClient() {
    clock = Clock();
}
void DriverClient::receiveTrip() {
    char buffer[1024];
    // RECEIVE TRIP FROM SERVER
    client->reciveData(buffer, sizeof(buffer));
    string tripString = createString(buffer, sizeof(buffer));
    Trip* trip;
    boost::iostreams::basic_array_source<char> device1(tripString.c_str(), tripString.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
    boost::archive::binary_iarchive ia1(s1);
    ia1 >> trip;

    // GIVE DRIVER THE TRIP
    driver.setTrip(trip);
    DriverClient::receiveCommand();
}

int DriverClient::receiveCommand() {
    char buffer[1024];
    client->reciveData(buffer, sizeof(buffer));
    string commandString = createString(buffer, sizeof(buffer));
    int command = 0;
    boost::iostreams::basic_array_source<char> device2(commandString.c_str(), commandString.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device2);
    boost::archive::binary_iarchive ia2(s4);
    ia2 >> command;
    if(command == 9) {
        DriverClient::receiveNextPoint();
    }
    if(command == 2) {
        DriverClient::receiveTrip();
    }
    if(command == 7) {
        DriverClient::closeSocket();
    }
}

void DriverClient::closeSocket() {
 client->~Socket();
}

void DriverClient::receiveNextPoint() {
    char buffer[1024];
    Trip newTrip;
        client->reciveData(buffer, sizeof(buffer));
        Point* p;
        string nextLocation = createString(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device3(nextLocation.c_str(), nextLocation.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device3);
        boost::archive::binary_iarchive ia(s3);
        ia >> p;
        Trip* tripP = driver.getTrip();
        tripP->updateStartPoint(p);
        driver.getTrip()->updateStartPoint(p);
        delete p;
        DriverClient::receiveCommand();
}
void DriverClient::openSocket(Driver *driverSent) {

    client = new Udp(0, 46323);
    int result = client->initialize();
    char buffer[1024];
    // SERIALIZATION

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driverSent;
    s.flush();

    cout << serial_str.c_str() << endl;
    // SENDS DRIVER TO SERVER
    int result1 = client->sendData(serial_str);
}
void DriverClient::receiveVehicle() {
    char buffer[1024];
    // GETS TAXI IN RETURN
    int resultData = client->reciveData(buffer, sizeof(buffer));

     // DESERIALIZATION
     string taxiString = createString(buffer, sizeof(buffer));
     Taxi *taxi;
     boost::iostreams::basic_array_source<char> device(taxiString.c_str(), taxiString.size());
     boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
     boost::archive::binary_iarchive ia(s2);
     ia >> taxi;
     //Checking taxi deserialization
     //GIVE DRIVER TAXI
    driver.setTaxi(*taxi);
    delete taxi;
}


Driver DriverClient::getDriver() {
    return this->driver;
}

string DriverClient::createString(char* buffer, int bufferSize) {
    std::string str(buffer, bufferSize);
    return str;
}