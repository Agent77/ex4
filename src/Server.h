/************************************************************
* File description: Server class header file. 				*
* Acts as server, receives clients, and controls the game
* flow of input/out, and serialization                     *
************************************************************/
#include <sstream>
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/access.hpp>
#include "City.h"
#include "Driver.h"
#include "Trip.h"
#include "Graph.h"
#include "Coordinate.h"
#include "TaxiCenter.h"
#include "sockets/Socket.h"
#include "Clock.h"

using namespace std;
using namespace boost::archive;
#ifndef EX2_GAMEFLOW_H
#define EX2_GAMEFLOW_H


class Server {

private:
    Socket* socket;
    City city;
    TaxiCenter tc;
    Clock clock;
    vector<Driver> waitingDrivers;
    vector<Taxi> vehicles;
    int portNum;
    Graph* g;
public:
    Server();
    /***********************************************************************
	* function name: run												   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: contains switch case which runs the main
    * flow of the input and client/server interactions                     *
	***********************************************************************/
    void run();
    /***********************************************************************
	* function name: initialize											   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: initializes the grid and obstacles for the
     * game                                                                *
	***********************************************************************/
    void initialize();
    //Trip getTripFromClient();
    /***********************************************************************
	* function name: SendTripToClient								       *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: Finds the correct trip according to the      *
     * current time, serializes it, and send it to the client              *
	***********************************************************************/
    void SendTripToClient();
    /***********************************************************************
	* function name: createClients										   *
	* The Input: string of port number													   *
	* The output: none										               *
	* The Function operation: opens a socket for the client to reach	   *
	***********************************************************************/
    int createClients(string port);
    /***********************************************************************
	* function name: assignVehicleToClient												   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: finds the right vehicle depending on driver
     * id, serializes it, and sends it to the client                       *
	***********************************************************************/
    void assignVehicleToClient();
    /***********************************************************************
	* function name: receiveDriver										   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: waits to receive serialized version of driver
     * sent from client and adds it to a vector of temporary drivers       *
	***********************************************************************/
    void receiveDriver();
    /***********************************************************************
	* function name: createString									       *
	* The Input: buffer and size of buffer													   *
	* The output: none										               *
	* The Function operation: creates a string from the buffer	           *
	***********************************************************************/
    string createString(char* buffer, int bufferSize);
    /***********************************************************************
	* function name: sendCommand										   *
	* The Input: int													   *
	* The output: none										               *
	* The Function operation: serializes and sends a command to client
     * Sends a number, depending on whether it wants the client to wait for
     * a trip, a new location, or a vehicle, or to close itself            *
	***********************************************************************/
    void sendCommand(int command);
    /***********************************************************************
	* function name: sendNextLocation									   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: drives the drivers, gets its next location,
     * serializes the point and sends it to client                         *
	***********************************************************************/
    void sendNextLocation();
    /***********************************************************************
	* function name: closeSockets										   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: notifies all clients to close themselves     *
	***********************************************************************/
    void closeSockets();

};


#endif //EX2_GAMEFLOW_H
