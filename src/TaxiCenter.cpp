
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
/*
 * adds driver to vector given an already created driver
 */
void TaxiCenter::addDriver(Driver d) {
    addDriver(d.getDriverId(), d.getAge(), d.getMaritalStatus(), d.getExp(), d.getVehicleId());
}



void TaxiCenter::updateMeters() {

}

int TaxiCenter::checkDestinations()  {
}



/*
 * Given a driver id, the function finds the driver with that
 * id and prints it's location.
 */
void TaxiCenter::requestDriverLocation(int driverId){
    vector<Driver>::iterator iter = drivers.begin();
    //compares each driver's id to the sent id
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
    //Assign taxi to driver
    vector<Taxi>::iterator taxi = taxis.begin();
    vector<Driver>::iterator driver = drivers.begin();
    //Giving taxis to each driver
    while(taxi != taxis.end()) {
        Taxi currentTaxi = *taxi;
        //Goes until finds a match in id
        while((*(driver)).getVehicleId() != (currentTaxi).getId() && driver != drivers.end()) {
            driver++;
        }
        Driver* driverMatch = &(*(driver));
        driverMatch->setTaxi(*taxi);
        taxi++;
    }
    taxis.clear();
    //Meaning the drivers are not all at (0,0)
    if(started) {
        vector<Driver>::iterator driverList = drivers.begin();
        vector<Trip>::iterator trip = trips.begin();
        while(driverList != drivers.end()) {
            trip = trips.begin();
            while (trip != trips.end()) {
                if ((*(driverList)).getTrip().getStart()->equalTo((*(trip)).getStart())) {
                    (*(driverList)).setTrip(*trip);
                }
                trip++;
            }
            driverList++;
        }
    }
        //First time the drivers are being given trips
    else {
        vector<Driver>::iterator driverList = drivers.begin();
        vector<Trip>::iterator trip = trips.begin();
        while (driverList != drivers.end() && trip != trips.end()) {
            (*(driverList)).setTrip((*(trip)));
            driverList++;
            trip++;
            count++;
        }
        /*from now on, function knows the drivers have already
        drove from (0,0)*/
        started = true;

    }
    //Clears so can continue entering in new trips
    trips.clear();
    return count;
}

/*
 * returns drivers
 */
vector <Driver> TaxiCenter::getDrivers (){
    return drivers;
}

/*
 * calls the drive() function of every driver to
 * alert it, so it can move to its destination.
 */
void TaxiCenter::driveAll() {
    assignDrivers();
    vector<Driver>::iterator currentDriver = drivers.begin();
    while(currentDriver != drivers.end()) {
        (*(currentDriver)).drive();
        currentDriver++;
    }
}

/*
 * addsa taxi to vector
 */
void TaxiCenter::addTaxi(Taxi t) {
    taxis.push_back(t);
}

/*
 * returns trips
 */
vector<Trip> TaxiCenter::getTrips() {
    return trips;
}

/*
 * adds trip to vector
 */
void TaxiCenter::addTrip(Trip t) {
    trips.push_back(t);
}

/*
 * adds a trip to vector, given parameters
 */
void TaxiCenter::addTrip(int tripId, int xStart, int yStart, int xEnd, int yEnd,
                         int numPassengers, double tariff) {
    Trip* trip = new Trip (tripId, xStart, yStart,xEnd,yEnd,numPassengers,tariff);
    trips.push_back(*trip);
}

/*
 * adds driver to vector.
 */
void TaxiCenter::addDriver(int driverId, int age, char mStatus, int vehicleId, int exp) {
    Driver *d = new Driver (driverId, age, mStatus, vehicleId, exp, map);
    drivers.push_back(*d);
}
