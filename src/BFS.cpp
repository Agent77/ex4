#include <sstream>
#include "BFS.h"
#include <boost/serialization/export.hpp>

using namespace std;
/*
 * Initializes the BFS source and destination based
 * on input, and sets the BFS graph to the graph object
 * that was sent.
 */


BFS::BFS(Graph* g) {
    this->graph = g;
}
/*
 * Prints the path from Source to Destination by
 * working backwards, from destination, and asking for the
 * node's 'previous' until arriving at the source.
 */
void BFS::PrintPath( Node* source, Node* destination) {
    Coordinate *path[100] = {};
    int count = 0;
    Node *currentNode = destination;
    Coordinate *c = ((*(currentNode)).getMyLocation());
    path[count] = c;
    count++;
    Node *n;
    do {
        n = ((*(graph)).getLocationOfPrev(currentNode));
        if (n->getMyLocation()->equalTo(source->getMyLocation())) {
            path[count] = n->getMyLocation();
            break;
        }
        path[count] = n->getMyLocation();
        count++;
        currentNode = n;
    } while (!(currentNode->getMyLocation()->equalTo(source->getMyLocation())));

    for (int i = count; i >= 0; i--) {
        Point point = path[i];
        cout << point << endl;
    }

    graph->deleteGraph();
}
/*
 * Gets the path from a source to a destination using a queue.
 * each iteration, it checks if it has arrived the destination.
 * Once it breaks, it prints the path.
 */
void BFS::getPath() {
    Node* newSource;
    Coordinate *c1;
    Coordinate *c2;
    myDeque.push(source);
    newSource = source;
    do {

        visitNeighbors(newSource);
        if (!myDeque.empty()) {
            myDeque.pop();
        }
        newSource = myDeque.front();
        if(newSource == NULL) {
        break;
        }
            c1 = (*(newSource)).getMyLocation();
            c2 = (*(destination)).getMyLocation();
    } while(!(c2->equalTo(c1)));
//    BFS::PrintPath(source, destination);
}

/*
 * Function visits all the neighbors of the sent node, n, by calling
 * the node's function 'getNeighbors()'. It then iterates
 * over the vector of neighbors, to check if they've been visited.
 * If they haven't, its sets their member 'visited' to true and
 * pushes them onto the queue.
 */
std::vector<Node*> BFS::visitNeighbors(Node* n) {
    std::vector<Node *> neighbors = (*(graph)).getNeighbors(n);
    vector<Node *>::iterator v = neighbors.begin();
    while (v != neighbors.end()) {
        if (!(*(*v)).isVisited()) {
            (*(*v)).visit();
            myDeque.push((*v));
        }
        v++;
    }
    return neighbors;
}

/*
 * This function first calls to the getPath function to set all the
 * previous Nodes, and then goes from
 * destination to source to get next place in path.
 */
Coordinate* BFS::getNextInPath(Coordinate* sLoc, Coordinate* dLoc){
    cout << "DLOC: "<<dLoc->getNextCoordinate(0) << endl;
    graph->getNodes();
    this->source =  graph->getNode(sLoc);
    this->source->visit();
    this->destination = graph->getNode(dLoc);
    cout << "DESTINATION X: " << destination->getLocation()[0] << endl;

    cout << "** AFTER SETTING SOURCE AND DESTINATION" << endl;
    this->getPath();
    cout << "** AFTER GET PATH **"<<endl;
    Node *node= destination;
    Node* previousNode;
    while (node != source && node->getPrev()!= NULL){
        previousNode = node;
        node = node->getPrev();
        cout << "REACHED WHILE LOOP" << endl;
    }
    return previousNode->getMyLocation();
}

Node* BFS::getSource() {
    return source;
}

Node* BFS::getDest() {
    return destination;
}

