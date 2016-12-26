
#ifndef EX1_GRAPH_H
#define EX1_GRAPH_H

#include <vector>
#include "Node.h"

/*
 * Graph is an abstract class which represents any kind of diagram. it has the abstract methods
 * for the diagram that are in charge of providing the information needed.
 */
class Graph {
public:
    Graph(){};
    ~Graph(){};
    virtual Node* getLocationOfPrev(Node* n) {};
    virtual std::vector<Node*> getNeighbors(Node* n)=0;
    virtual Node* getNode(Coordinate* p){};
    virtual void deleteGraph() {};
    virtual void addObstacle(Coordinate* p){};
    virtual void resetGraph(){};
};


#endif //EX1_GRAPH_H
