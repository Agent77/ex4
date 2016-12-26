
#include "GameFlow.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include <iostream>

/*
 * This initializes the general grid for the map and
 * creates the taxi center with it.
 */
void GameFlow::initialize() {
    string obstacles;
    string size1;
    string size2;
    int obstacleCount;

    //To be used later as graph size
    cin >> size1;
    cin >> size2;
    Graph *grid = city.createGraph(size1, size2);

    //Checks for obstacles
    cin >> obstacles;
    std::istringstream(obstacles) >> obstacleCount;
    if (obstacleCount != 0) {
        string obstacle;
        for (int count = 0; count < obstacleCount; count++) {
            cin >> obstacle;
            Coordinate* c = city.createCoordinate(obstacle);
            grid->addObstacle(c);
        }
    }
    BFS *bfs = new BFS(grid);
    tc = TaxiCenter(grid);
}

/*
 * function to run main the
 * switch case to accept user input constantly.
 */
void GameFlow::run() {
    int run = 1;
    char action1;
    int driverId;
    string input;
    string s;

    while (run) {
        cin >> action1;
        int action = (int)action1 - 48;
        switch(action) {
            case 1: //Insert Driver
            {
                cin >> input;
                Driver d = city.createDriver(input);
                tc.addDriver(d);
                break;
            }
            case 2: { //Insert Trip
                cin >> input;
                Trip t = city.createTrip(input);
                tc.addTrip(t);
                break;
            }
            case 3: { //Insert taxi
                cin >> s;
                Taxi t = city.createTaxi(s);
                tc.addTaxi(t);
                break;
            }
            case 4: { //Insert driver
                cin >> driverId;
                tc.requestDriverLocation(driverId);
                break;
            }
            case 6: { //Drives all to destinations
                tc.driveAll();
                break;
            }
            case 7:
                run = 0;
                break;
            default:
                break;
        }
    }
}

