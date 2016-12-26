//
// Created by Tiki Lobel on 11/17/16.
//

#ifndef GTESTEX3_BFS_H
#define GTESTEX3_BFS_H
#include "Node.h"
#include <queue>
#include "Graph.h"
#include "Grid.h"
#include "Coordinate.h"
#include "Searchable.h"

/*
 * Class which performs the Breadth-First Search on any given graph/diagram.
 * It contains the graph, start, and end-point, in Node pointer form.
 */
using namespace std;
class BFS: public Searchable {
private:
    std::queue<Node*> myDeque;
    Node* source;
    Graph* graph;
    Node* destination;

public:
    BFS(){};
    BFS(Graph* g);
    Node* getSource();
    Node* getDest();void getPath();
    void PrintPath(Node* s, Node* d);
    std::vector<Node*> visitNeighbors(Node* n);
    Coordinate* getNextInPath(Coordinate* sLoc, Coordinate* dLoc);

};

#endif //EXONE_BFS_H