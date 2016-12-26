
#include "GameFlow.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include <iostream>


/*
* Initializes the grid and taxi center.
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
   // std::istringstream(obstacles) >> obstacleCount;
    //int obstacleCount ;//= atoi(obstacles);
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
* runs the switch case so the user can constantly 
* add input.
*/
void GameFlow::run() {
    int run = 1;
    char action1;
    int driverId;
    string input;
    string s;

//Actions the user can perform
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
            case 2: {
                cin >> input;
                Trip t = city.createTrip(input);
                tc.addTrip(t);
                break;
            }
            case 3: {
                cin >> s;
                Taxi t = city.createTaxi(s);
                tc.addTaxi(t);
                break;
            }
            case 4: {
                cin >> driverId;
                tc.requestDriverLocation(driverId);
                break;
            }
            case 6: {
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

