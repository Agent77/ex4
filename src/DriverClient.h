//
// Created by Tiki Lobel on 12/26/16.
//

#ifndef PRACTICE6_DRIVERCLIENT_H
#define PRACTICE6_DRIVERCLIENT_H


#include <boost/iostreams/device/array.hpp>
#include "Clock.h"

class DriverClient {
private:
    Socket* client;
    Driver driver;
    Clock clock;
public:
    DriverClient();
    void openSocket(Driver* d);
    void ReceiveTrip();
    void ReceiveCommand();
    Driver getDriver();
};


#endif //PRACTICE6_DRIVERCLIENT_H
