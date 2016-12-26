#ifndef EX1_GRID_H
#define EX1_GRID_H
#include "Node.h"
#include "Point.h"
#include "Graph.h"
#include <string.h>
#include <vector>
/*
 * Grid is a specific implementation of Graph, an
 * abstract class to place objects in a certain location.
 * Its maximum size is 10x10, and coordinate type is Point,
 * a Coordinate implementation with 2 coordinates, x and y.
 * It can find the neighbors of each object, and create
 * a Node based off of a given Coordinate.
 */
class Grid : public Graph {
private:
    Node* arrayOfPtrsToNodes[10][10];
    int sizeX;
    int sizeY;
public:
    Grid(){};
    ~Grid();
    Grid(int sizeX, int sizeY);
    Node* getLocationOfPrev(Node* n);
    std::vector<Node*> getNeighbors(Node* node);
    Node* getNode(Coordinate* p);
    void deleteGraph();
    void addObstacle(Coordinate* p);
    void resetGraph();

};
#endif //EX1_GRID_H