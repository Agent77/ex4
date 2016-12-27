/*
 * The main class of the project is in charge of parsing
 * the input and creating the relevant
 * objects. then calling the method of the
 * BFS in order to get the right path.
 */

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include "Point.h"
#include "BFS.h"
#include "Driver.h"
#include "City.h"
#include "TaxiCenter.h"
//#include <boost/lexical_cast.hpp>
//#include <boost/tokenizer.hpp>
#include "Server.h"


using namespace std;

int main() {
// create and open a character archive for output
    std::ofstream ofs("serializedDriver.txt");

    // create class instance
    Driver *driver = new Driver(34 ,4 ,'W', 0, 77);


    // save data to archive
    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << driver;
    // archive and stream closed when destructors are called

    // ... some time later restore the class instance to its orginal state
    int driverId;

    // create and open an archive for input
    std::ifstream ifs("serializedDriver.txt");
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> driverId;
    // archive and stream closed when destructors are called
}
