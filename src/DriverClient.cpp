#include "sockets/Udp.h"

//
// Created by Tiki Lobel on 12/26/16.
//
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    std::cout << "** IN CLIENT MAIN **\n" << std::endl;
    Udp client = Udp(0, 5555);
    int result = client.initialize();
    cout << "RESULT: " << result << endl;
    cout << "CLIENT PORT: " << client.getPortNum() << endl;
    std::cout << "** AFTER INITIALIZE **\n" << std::endl;
    char buffer[1024];
    client.sendData("HEYYYYYYOOOOO");
    std::cout << "** AFTER send Data **\n" << std::endl;

    client.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    std::cout << "** AFTER SEND DATA **\n" << std::endl;


    return 0;
}
    //RECEIVE INFO FOR DRIVER FROM CONSOLE

    //CREATE DRIVER OBJECT

    //SERIALIZE AND SEND DRIVER TO SERVER VIA SOCKET

    //WAITS FOR VEHICLE

    //WAITS FOR 'GO'
