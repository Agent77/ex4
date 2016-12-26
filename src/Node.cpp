#include "Node.h"

using namespace std;

/*
 * The default constructor which sets the visited member to false.
 */
Node::Node() {
    visited = false;
    obstacle = false;
}

/*
 * The constructor gets a coordinate object, initializes my location member to be with the given
 * info and sets the visited member to false.
 */
Node::Node(Coordinate *p) {
    myLocation = p->getMyLocation();
    visited = false;
    obstacle = false;
}

/*
 * getLocation returns the coordinates of the node.
 */
int* Node::getLocation() {
    return myLocation->getCoordinates();
}

/*
 * isVisited returns the value of the member visited. the value would be true if this node has been
 * visited on the grid and false otherwise.
 */
bool Node::isVisited() {
    return visited;
}
/*
 * visit is called in order to set the value of visited to true when the node is visited for the
 * first time on the grid.
 */
void Node::visit() {
    visited = true;
}
/*
 * getPrev returns the previous node of the current one.
 */
Node* Node::getPrev() {
    return prev;
}

/*
 * setPrev sets the previous node
 * of the current one at first time it's visited.
 */
void Node::setPrev(Node& n) {
    prev = &n;
}
Node::~Node() {

}

Coordinate* Node::getMyLocation() {
    return myLocation;
}

/*
 * sets member to true so it
 * knows it is an obstacle
 */
void Node::makeObstacle() {
    obstacle = true;
}

bool Node::isObstacle() {
    return obstacle;
}

/*
 * resets its members so when asked again
 * for example "if visited" next time a bfs is
 * run on the same grid, it won't say yes just because
 * last time it was set to true.
 */
void Node::resetNode() {
    visited=false;
    prev=NULL;
}