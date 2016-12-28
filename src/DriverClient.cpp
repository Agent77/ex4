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
    client.ReceiveTrip();
    client.ReceiveCommand();
    return 0;
}
DriverClient::DriverClient() {
    clock = Clock();
}
void DriverClient::ReceiveTrip() {

    char buffer[1024];
    // RECEIVE TRIP FROM SERVER
    client->reciveData(buffer, sizeof(buffer));
    string tripString = buffer;
    Trip *trip;
  /*  boost::iostreams::basic_array_source<char> device1(tripString.c_str(), tripString.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
    boost::archive::binary_iarchive ia1(s1);
    ia1 >> trip;*/

    // GIVE DRIVER THE TRIP
    driver.setTrip(*trip);
    DriverClient::ReceiveCommand();
}
void DriverClient::ReceiveCommand() {
    char buffer[1024];
    Trip newTrip;
    // GET COMMAND FROM SERVER
    do {
        client->reciveData(buffer, sizeof(buffer));
        string commandString = buffer;
        int command = 0;
       /* boost::iostreams::basic_array_source<char> device2(commandString.c_str(), commandString.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device2);
        boost::archive::binary_iarchive ia2(s4);
        ia2 >> command;*/
        // DOES ACTION ACCORDING TO COMMAND
        newTrip = driver.drive();
        clock.increaseTime();
        string serial_str;
        /*boost::iostreams::back_insert_device<std::string> inserter2(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s3(inserter2);
        boost::archive::binary_oarchive oa2(s3);
        oa2 << newTrip;
        s3.flush();*/

        // SENDS NEW TRIP TO SERVER TO UPDATE
       // client->sendData(serial_str);
    } while(!driver.arrived());
    DriverClient::ReceiveTrip();
}
void DriverClient::openSocket(Driver *driver) {
    // SET UP SOCKET
    client = new Udp(0, 5555);
    int result = client->initialize();
    char buffer[1024];
    // SERIALIZATION
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    cout<<serial_str.c_str()<<endl;
    // SENDS DRIVER TO SERVER
    client->sendData(serial_str);
    cout<<"##driver sent##"<<endl;

    // GETS TAXI IN RETURN
    client->reciveData(buffer, sizeof(buffer));

    // DESERIALIZATION
    string taxiString = buffer;
    Taxi *taxi;
    /*boost::iostreams::basic_array_source<char> device(taxiString.c_str(), taxiString.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> taxi;*/

    //GIVE DRIVER TAXI
    driver->setTaxi(*taxi);
}

Driver DriverClient::getDriver() {
    return this->driver;
}