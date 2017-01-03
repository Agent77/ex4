//
// Created by Tiki Lobel on 12/26/16.
//

#ifndef PRACTICE6_DRIVERCLIENT_H
#define PRACTICE6_DRIVERCLIENT_H

#include "City.h"
#include <boost/iostreams/device/array.hpp>
#include "Clock.h"
#include <boost/serialization/access.hpp>
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
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

class DriverClient {
private:
    Socket* client;
    Driver driver;
    Clock clock;
public:
    DriverClient();
    void openSocket(Driver* driver, int portNumber);
    void receiveTrip();
    int receiveCommand();
    void receiveNextPoint();
    void closeSocket();
    Driver getDriver();
    string createString(char* buffer, int bufferSize);
    void receiveVehicle();
};


#endif //PRACTICE6_DRIVERCLIENT_H
