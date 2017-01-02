#include "sockets/Udp.h"
#include "Driver.h"
#include "DriverClient.h"
#include "LuxuryCab.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
using namespace boost::archive;
int main() {
    City c = City();

    string d;
    cin >> d;
    Driver dr = c.createDriver(d);
    Driver* driver = &dr;
    cout << "DRIVER INFO: "<<endl;
    cout << "ID: " << driver->getDriverId()<<endl;
    cout << "START OF TRIP: " << driver->getTrip()->getStartX() << "," << driver->getTrip()->getStartY()<<endl;
    cout << "END OF TRIP: " << driver->getTrip()->getEndX() << "," << driver->getTrip()->getEndY()<<endl;

    DriverClient client = DriverClient();

    client.openSocket(driver);
    client.receiveVehicle();
    client.ReceiveTrip();
   // client.ReceiveCommand();
    return 0;
}
DriverClient::DriverClient() {
    clock = Clock();
}
void DriverClient::ReceiveTrip() {
    char buffer[1024];
    // RECEIVE TRIP FROM SERVER
    client->reciveData(buffer, sizeof(buffer));
    string tripString = createString(buffer, sizeof(buffer));
    Trip* trip;
    boost::iostreams::basic_array_source<char> device1(tripString.c_str(), tripString.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
    boost::archive::binary_iarchive ia1(s1);
    ia1 >> trip;

    cout << "TRIP START X: "<< trip->getStartX() << endl;
    cout << "TRIP START Y: "<< trip->getStartY()  << endl;
    cout << "TRIP END X: "<< trip->getEndX() << endl;
    cout << "TRIP END Y: "<< trip->getEndY() << endl;

    // GIVE DRIVER THE TRIP
    //cout << "DOES DRIVER GET AN ID?: "<< driver.getDriverId() << endl;
    driver.setTrip(trip);

    cout << "INFO IN OPEN SOCKET:" << endl;
    cout << "DRIVER INFO: "<<endl;
    cout << "ID: " << driver.getDriverId()<<endl;
    cout << "START OF TRIP: " << driver.getTrip()->getStartX() << "," << driver.getTrip()->getStartY()<<endl;
    cout << "END OF TRIP: " << driver.getTrip()->getEndX() << "," << driver.getTrip()->getEndY()<<endl;
    DriverClient::ReceiveCommand();
}
void DriverClient::ReceiveCommand() {
    char buffer[1024];
    Trip newTrip;
    // GET COMMAND FROM SERVER

    cout << "BEFORE RECEIVING COMMAND"<< endl;
    do {
        /*client->reciveData(buffer, sizeof(buffer));
        string commandString = createString(buffer, sizeof(buffer));
        int command = 0;
        boost::iostreams::basic_array_source<char> device2(commandString.c_str(), commandString.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device2);
        boost::archive::binary_iarchive ia2(s4);
        ia2 >> command;*/

        client->reciveData(buffer, sizeof(buffer));
        Point* p;
        string nextLocation = createString(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device3(nextLocation.c_str(), nextLocation.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device3);
        boost::archive::binary_iarchive ia(s3);
        ia >> p;


        cout << "P.X :" << p->getNextCoordinate(0);
        cout << "P.Y: " << p->getCoordinates()[1];
        Trip* tripP = driver.getTrip();
        tripP->updateStartPoint(p);

        cout << "INFO IN RECEIVE COMMAND AFTER MOVE:" << endl;
        cout << "DRIVER INFO: "<<endl;
        cout << "ID: " << driver.getDriverId()<<endl;
        cout << "START OF TRIP: " << driver.getTrip()->getStartX() << "," << driver.getTrip()->getStartY()<<endl;
        cout << "END OF TRIP: " << driver.getTrip()->getEndX() << "," << driver.getTrip()->getEndY()<<endl;

        driver.getTrip()->updateStartPoint(p);
        // SENDS NEW TRIP TO SERVER TO UPDATE
       // client->sendData(serial_str);
    } while(!driver.arrived());

    DriverClient::ReceiveTrip();
}
void DriverClient::openSocket(Driver *driverSent) {
    driver = *driverSent;
    cout << "INFO IN OPEN SOCKET:" << endl;
    cout << "DRIVER INFO: "<<endl;
    cout << "ID: " << driver.getDriverId()<<endl;
    cout << "START OF TRIP: " << driver.getTrip()->getStartX() << "," << driver.getTrip()->getStartY()<<endl;
    cout << "END OF TRIP: " << driver.getTrip()->getEndX() << "," << driver.getTrip()->getEndY()<<endl;
    // SET UP SOCKET
    client = new Udp(0, 5555);
    int result = client->initialize();
    char buffer[1024];
    // SERIALIZATION

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driverSent;
    s.flush();

    cout << serial_str.c_str() << endl;
    // SENDS DRIVER TO SERVER
    int result1 = client->sendData(serial_str);
}
void DriverClient::receiveVehicle() {
    char buffer[1024];
    // GETS TAXI IN RETURN
    int resultData = client->reciveData(buffer, sizeof(buffer));

     // DESERIALIZATION
     string taxiString = createString(buffer, sizeof(buffer));
     Taxi *taxi;
     boost::iostreams::basic_array_source<char> device(taxiString.c_str(), taxiString.size());
     boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
     boost::archive::binary_iarchive ia(s2);
     ia >> taxi;
     //Checking taxi deserialization
     //GIVE DRIVER TAXI
     driver.setTaxi(*taxi);
    cout << "INFO IN RECEIVE VEHICLE:" << endl;
    cout << "DRIVER INFO: "<<endl;
    cout << "ID: " << driver.getDriverId()<<endl;
    cout << "START OF TRIP: " << driver.getTrip()->getStartX() << "," << driver.getTrip()->getStartY()<<endl;
    cout << "END OF TRIP: " << driver.getTrip()->getEndX() << "," << driver.getTrip()->getEndY()<<endl;
}


Driver DriverClient::getDriver() {
    return this->driver;
}

string DriverClient::createString(char* buffer, int bufferSize) {
    std::string str(buffer, bufferSize);
    return str;
}