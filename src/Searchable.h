//
// Created by Tiki Lobel on 12/15/16.
//

#ifndef GTESTEX3_SEARCHABLE_H
#define GTESTEX3_SEARCHABLE_H

#include <boost/serialization/access.hpp>
#include <queue>
#include "Node.h"
#include "Graph.h"

/*
* general class that searches, in no partcilar order,
* a given grid.
*/
class Searchable {
    friend class boost::serialization::access;

    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {
        ar & myDeque;
        ar & source;
        ar & graph;
        ar & destination;
    }

protected:
    std::queue<Node*> myDeque;
    Node* source;
    Graph* graph;
    Node* destination;
public:
    Searchable() {};
    ~Searchable() {};
    Searchable(Graph* g) {
        graph = g;
    };
    virtual void getPath() = 0;
    virtual void PrintPath(Node* s, Node* d) = 0;
    virtual std::vector<Node*> visitNeighbors(Node* n) = 0;
    virtual Node* getDest(){};
    virtual Node* getSource(){};
    virtual Coordinate* getNextInPath(Coordinate* sLoc, Coordinate* dLoc) = 0;
};


#endif //GTESTEX3_SEARCHABLE_H
