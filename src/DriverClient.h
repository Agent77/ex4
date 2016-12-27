//
// Created by Tiki Lobel on 12/26/16.
//

#ifndef PRACTICE6_DRIVERCLIENT_H
#define PRACTICE6_DRIVERCLIENT_H


#include <boost/iostreams/device/array.hpp>

class DriverClient {
private:
    Socket* client;
    Driver driver;
public:
    void openSocket();
    void ReceiveTrip();
    void ReceiveCommand();
    Driver getDriver();
};


#endif //PRACTICE6_DRIVERCLIENT_H
