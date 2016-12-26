#ifndef EX1_NODE_H
#define EX1_NODE_H
#include "Node.h"
#include "Point.h"
#include "Coordinate.h"

/*
 * Node is a class that represents each object on the grid. it has a reference to the node that
 * we came from on the grid, it's location and a member that says whether it has been visited
 * on the grid or not.
 */

class Node {
private:
    Coordinate* myLocation;
    Node* prev;
    bool visited;
    bool obstacle;
public:
    Node* neighbors;
    Node();
    ~Node();
    Node(Coordinate* c);
    bool isVisited();
    bool isObstacle();
    void visit();
    void makeObstacle();
    Node* getPrev();
    void setPrev(Node& n);
    int* getLocation();
    Coordinate* getMyLocation();
    void resetNode();
};

#endif //EX1_NODE_H