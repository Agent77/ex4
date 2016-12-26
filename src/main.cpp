/*
 * The main class of the project is in charge of parsing
 * the input and creating the relevant
 * objects. then calling the method of the
 * BFS in order to get the right path.
 */

#include <iostream>
#include "Point.h"
#include "BFS.h"
#include "Driver.h"
#include "City.h"
#include "TaxiCenter.h"
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include "GameFlow.h"


using namespace std;

int main() {
    GameFlow gf = GameFlow();
    gf.initialize();
    gf.run();
}
