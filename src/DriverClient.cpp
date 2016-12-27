#include "sockets/Udp.h"
#include "Driver.h"
#include "DriverClient.h"

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

int main() {
// GET INITIAL INFO FROM CONSOLE INPUT

    DriverClient client = DriverClient();
    client.openSocket();
    client.ReceiveTrip();
    while(!client.getDriver().arrived()) {
        client.ReceiveCommand();
    }
    client.ReceiveTrip();
    //return to loop
    return 0;
}

void DriverClient::ReceiveTrip() {

    char buffer[1024];
    // RECEIVE TRIP FROM SERVER
    client->reciveData(buffer, sizeof(buffer));
    string tripString = buffer;
    Trip *trip;
    boost::iostreams::basic_array_source<char> device1(tripString.c_str(), tripString.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
    boost::archive::binary_iarchive ia1(s1);
    ia1 >> trip;

    // GIVE DRIVER THE TRIP
    driver.setTrip(*trip);
}
void DriverClient::ReceiveCommand() {
    char buffer[1024];
    // GET COMMAND FROM SERVER
    client->reciveData(buffer, sizeof(buffer));
    string commandString = buffer;
    int command = 0;
    boost::iostreams::basic_array_source<char> device2(commandString.c_str(), commandString.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device2);
    boost::archive::binary_iarchive ia2(s4);
    ia2 >> command;

    // DOES ACTION ACCORDING TO COMMAND
    Trip newTrip = driver.drive();
    string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter2(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s3(inserter2);
    boost::archive::binary_oarchive oa2(s3);
    oa2 << newTrip;
    s3.flush();

    // SENDS NEW TRIP TO SERVER TO UPDATE
    client->sendData(serial_str);
}
void DriverClient::openSocket() {
    // SET UP SOCKET
    client = new Udp(0, 5555);
    int result = client->initialize();
    char buffer[1024];

    // SERIALIZATION
    Driver* driver = new Driver(34, 5, 'W', 2, 77);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    // SENDS DRIVER TO SERVER
    client->sendData(serial_str);

    // GETS TAXI IN RETURN
    client->reciveData(buffer, sizeof(buffer));

    // DESERIALIZATION
    string taxiString = buffer;
    Taxi *taxi;
    boost::iostreams::basic_array_source<char> device(taxiString.c_str(), taxiString.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> taxi;

    //GIVE DRIVER TAXI
    driver->setTaxi(*taxi);
}

Driver DriverClient::getDriver() {
    return this->driver;
}