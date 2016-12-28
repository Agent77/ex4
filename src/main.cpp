/*
 * The main class of the project is in charge of parsing
 * the input and creating the relevant
 * objects. then calling the method of the
 * BFS in order to get the right path.
 */


#include <fstream>

#include "Point.h"
#include "BFS.h"
#include "Driver.h"
#include "City.h"
#include "TaxiCenter.h"
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
#include "Server.h"


using namespace std;

int main() {
    Point *gp = new Point(1,5);

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << gp;
    s.flush();

    cout << serial_str << endl;

    Point *gp2;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> gp2;

    cout << *gp2;

    delete gp;
    delete gp2;
    return 0;
}
