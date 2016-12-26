//
// Created by Tiki Lobel on 12/26/16.
//

#include "TaxiCenterServer.h"
#include "sockets/Udp.h"

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;
int main() {
    std::cout << "** IN TAXI CENTER MAIN **\n" << std::endl;

    Socket* taxiCenterServer = new Udp(1, 777);
    taxiCenterServer->initialize();
    char buffer[1024];
//RECEIVES ALL INITIAL INPUT

//RECEIVES DRIVER OBJECT TO DESERIALIZE
    taxiCenterServer->reciveData(buffer, sizeof(buffer));
//RETURNS TO CLIENT A VEHICLE with serialization
    taxiCenterServer->sendData("Hello from the server!\n");
    return 0;
}