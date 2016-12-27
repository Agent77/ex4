//
// Created by Tiki Lobel on 12/26/16.
//

#ifndef PRACTICE6_DRIVERCLIENT_H
#define PRACTICE6_DRIVERCLIENT_H


#include <boost/iostreams/device/array.hpp>

class DriverClient {
public:
    boost::iostreams::basic_array_source<char> device;
    void openSocket();
};


#endif //PRACTICE6_DRIVERCLIENT_H
