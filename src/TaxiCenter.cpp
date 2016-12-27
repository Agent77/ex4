
#include "TaxiCenter.h"
#include "Driver.h"
#include "sockets/Udp.h"

using namespace std;

#include "TaxiCenterServer.h"
#include "sockets/Udp.h"

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

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

    Socket* taxiCenterServer = new Udp(1, 5555);
    int result = taxiCenterServer->initialize();
    cout << "RESULT: " << result << endl;
    std::cout << "** AFTER INITIALIZE **\n" << std::endl;

    char buffer[1024];
    taxiCenterServer->reciveData(buffer, sizeof(buffer));
    std::cout << "** AFTER REC DATA **\n" << std::endl;

    cout << buffer << endl;
    taxiCenterServer->sendData("Hello from the server!\n");
    return 0;
}
//RECEIVES ALL INITIAL INPUT
//RECEIVES DRIVER OBJECT TO DESERIALIZE
//RETURNS TO CLIENT A VEHICLE with serialization

TaxiCenter::TaxiCenter() {
    started = false;
}

TaxiCenter::TaxiCenter(Graph* map1) {
    map = map1;
    started = false;
}
//Checks BFS to find the closest driver to passenger source
Driver TaxiCenter::findClosestDriver(Trip t) {

}

void TaxiCenter::addDriver(Driver d) {
    addDriver(d.getDriverId(), d.getAge(), d.getMaritalStatus(), d.getExp(), d.getVehicleId());
            //driverId, int age, char mStatus, int vehicleId, int exp
}


void TaxiCenter::updateMeters() {

}

int TaxiCenter::checkDestinations()  {
}


/*
*finds a driver based on a requested id, and prints their
* current location.
*/

void TaxiCenter::requestDriverLocation(int driverId){
    vector<Driver>::iterator iter = drivers.begin();
    while((*(iter)).getDriverId() != driverId) {
        iter++;
    }
    Coordinate* p = (*(iter)).getTrip().getStart();
    cout<<*p<<endl;
    delete p;

}

/*
 * Function assigns trips and taxis to drivers.
 * If drivers have already been assigned a trip once from
 * their starting point (0,0), the function pairs up trips
 * with the same ride id as the driver id.
 */
int TaxiCenter::assignDrivers() {

    int count = 0;

    //Assign taxi to driver according to....
    vector<Taxi>::iterator taxi = taxis.begin();
    vector<Driver>::iterator driver = drivers.begin();

    while(taxi != taxis.end()) {
        Taxi currentTaxi = *taxi;
        while((*(driver)).getVehicleId() != (currentTaxi).getId() && driver != drivers.end()) {
            driver++;
        }
        Driver* driverMatch = &(*(driver));
        driverMatch->setTaxi(*taxi);
        taxi++;
    }
    taxis.clear();
    //Meaning drivers already drove away from (0,0)
    if(started) {
        vector<Driver>::iterator driverList = drivers.begin();
        vector<Trip>::iterator trip = trips.begin();
        while(driverList != drivers.end()) {
            trip = trips.begin();
            while (trip != trips.end()) {
            		//matching up trips and driver current locations
                if ((*(driverList)).getTrip().getStart()->equalTo((*(trip)).getStart())) {
                    (*(driverList)).setTrip(*trip);
                }
                trip++;
            }
            driverList++;
        }

        }
    else {
		//drivers all at (0,0))
        vector<Driver>::iterator driverList = drivers.begin();
        vector<Trip>::iterator trip = trips.begin();
        while (driverList != drivers.end() && trip != trips.end()) {
            (*(driverList)).setTrip((*(trip)));
            driverList++;
            trip++;
            count++;
        }
        //So function knows the drivers have already been assigned a trip before
        started = true;

    }
    trips.clear();
    return count;

}

vector <Driver> TaxiCenter::getDrivers (){
    return drivers;
}

/*
* alerts all drivers to move.
*/
void TaxiCenter::driveAll() {
    assignDrivers();
    vector<Driver>::iterator currentDriver = drivers.begin();
    while(currentDriver != drivers.end()) {
        (*(currentDriver)).drive();
        currentDriver++;
    }
}

void TaxiCenter::addTaxi(Taxi t) {
    taxis.push_back(t);
}

vector<Trip> TaxiCenter::getTrips() {
    return trips;
}


void TaxiCenter::addTrip(Trip t) {
    trips.push_back(t);
}

void TaxiCenter::addTrip(int tripId, int xStart, int yStart, int xEnd, int yEnd,
                         int numPassengers, double tariff) {
    Trip* trip = new Trip (tripId, xStart, yStart,xEnd,yEnd,numPassengers,tariff);
    trips.push_back(*trip);
}

void TaxiCenter::addDriver(int driverId, int age, char mStatus, int vehicleId, int exp) {
    Driver *d = new Driver (driverId, age, mStatus, vehicleId, exp, map);
    drivers.push_back(*d);
}

void TaxiCenter::updateDriverTrip(Trip newTrip){
    vector<Driver>::iterator driver = drivers.begin();
    while (newTrip.getId()!=(*(driver)).getTrip().getId()){
        driver++;
    }
    (*(driver)).setTrip(newTrip);
}

Taxi TaxiCenter::assignTaxi(int driverId){
    vector<Driver>::iterator driver = drivers.begin();
    vector<Taxi>::iterator taxi = taxis.begin();
    while ((*(driver)).getDriverId()!=driverId){
        driver++;
        taxi++;

    }
    (*(driver)).setTaxi((*(taxi)));
    return *(taxi);
}

Trip TaxiCenter::getNextTrip(int currentTime) {
    vector<Trip>::iterator trip = trips.begin();
    while ((*(trip)).getTripTime()!= currentTime){
        trip++;
    }
    Trip nextTrip= *(trip);
    trips.erase (trip);
    return nextTrip;
}

int TaxiCenter::checkTripTimes(int currentTime) {
    int counter =0;
    for (int i=0; i<trips.size();i++) {
        if (trips[i].getTripTime() == currentTime) {
            counter++;
        }
    }
    return counter;
}
