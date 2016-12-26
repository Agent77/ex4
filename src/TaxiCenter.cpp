
#include "TaxiCenter.h"
#include "Driver.h"
using namespace std;
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