
#include "TaxiCenter.h"
#include "Driver.h"
#include "sockets/Udp.h"

using namespace std;


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
/*int main() {
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
}*/

TaxiCenter::TaxiCenter(Graph* map1) {
    map = map1;
    started = false;
}
//Checks BFS to find the closest driver to passenger source
Driver TaxiCenter::findClosestDriver(Trip t) {

}

void TaxiCenter::addDriver(Driver d) {
    drivers.push_back(d);
   // addDriver(d.getDriverId(), d.getAge(), d.getMaritalStatus(), d.getExp(), d.getVehicleId());

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
    Point point = Point((*(iter)).getTrip()->getStartX(),(*(iter)).getTrip()->getStartY());
    cout << "X: "<<(*(iter)).getTrip()->getStartX()<< endl;
    cout << "Y: "<<(*(iter)).getTrip()->getStartY()<< endl;
    Coordinate* p = &point;
    cout<<*p<<endl;

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
        vector<Trip>::iterator trip;// = trips.begin();
        while(driverList != drivers.end()) {
            trip = trips.begin();
            while (trip != trips.end()) {
            		//matching up trips and driver current locations
                if ((*(driverList)).getTrip()->getStartX() == ((*(trip)).getStartX())) {
                    if ((*(driverList)).getTrip()->getStartY() == (*(trip)).getStartY()) {
                        Trip t = (*(trip));
                        (*(driverList)).setTrip((&t));
                    }
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
            (*(driverList)).setTrip(&(*(trip)));
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

void TaxiCenter::assignTrip(Trip t) {

}
vector <Driver> TaxiCenter::getDrivers (){
    return drivers;
}

/*
* alerts all drivers to move.
*/
Coordinate* TaxiCenter::driveAll() {
    cout << "in DRIVE ALL" << endl;
    assignDrivers();
    cout << "AFTER ASSIGN DRIVER"<< endl;
    Trip* t;
    vector<Driver>::iterator currentDriver = drivers.begin();
   // while(currentDriver != drivers.end()) {
        (drivers).at(0).setMap(map);
        map->getNodes();
         t = drivers.at(0).drive();
      //  currentDriver++;
    //}
    cout << "AFTER LOOP: " << t->getStart().getX();
    Point p = t->getStart();
    Coordinate* c = &p;
    return c;
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

void TaxiCenter::addDriver(int driverId, int age, char mStatus, int exp, int vehicleId) {
   Driver *d = new Driver (driverId, age, mStatus, exp, vehicleId);
    drivers.push_back(*d);
}

void TaxiCenter::updateDriverTrip(Trip newTrip, int place){
    drivers.at(place).setTrip(&newTrip);
}
void TaxiCenter::updateDriverTrip(Trip t) {
    vector<Driver>::iterator driver = drivers.end();
    (*(driver)).setTrip(&t);
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
    while ((*(trip)).getTripTime()< currentTime && trip != trips.end()){ //TODO does this stop loop
        trip++;
    }
    Trip nextTrip= *(trip);
    trips.erase(trip);
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

Graph* TaxiCenter::getMap() {
    return map;
}

void TaxiCenter::resetDrivers(vector<Driver> ds) {
    drivers = ds;
}

void TaxiCenter::deleteDriver(int i) {
    drivers.erase(drivers.begin()+i);
}