//
// Created by Tiki Lobel on 12/26/16.
//

#include "DriverClient.h"
#include "sockets/Socket.h"
#include "sockets/Udp.h"


int main(int argc, char *argv[]) {

    std::cout << "** IN CLIENT MAIN **\n" << std::endl;
    Socket* client = new Udp(0, 777);
    client->initialize();
    char buffer[1024];
    client->reciveData(buffer, sizeof(buffer));
    client ->sendData("HEYYYYYYOOOOO");




    //RECEIVE INFO FOR DRIVER FROM CONSOLE

    //CREATE DRIVER OBJECT

    //SERIALIZE AND SEND DRIVER TO SERVER VIA SOCKET

    //WAITS FOR VEHICLE

    //WAITS FOR 'GO'


    return 0;
}
