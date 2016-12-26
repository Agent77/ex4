
#include "src/sockets/Udp.h"
#include <unistd.h>
#include <iostream>


using namespace std;


// CLIENT MAIN


int main(int argc, char *argv[]) {
    std::cout << "** IN CLIENT MAIN ** " << std::endl;

    //RECEIVE INFO FOR DRIVER FROM CONSOLE

    //CREATE DRIVER OBJECT

    //SERIALIZE AND SEND DRIVER TO SERVER VIA SOCKET

    //WAITS FOR VEHICLE

    //WAITS FOR 'GO'






    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    char buffer[1024];
    udp.sendData("hello");
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;


    return 0;
}