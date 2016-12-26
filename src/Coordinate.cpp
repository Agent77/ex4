#include "Coordinate.h"
/*
 * allows any function to request an objects location,
 * without having to know how many coordinates it contains
 * (ie, which dimension it is in)
 */
int Coordinate::getNextCoordinate(int i) {
    return locs[i];
}

/*
 * Copies the coordinates from one point to another
 */
Coordinate::Coordinate(Coordinate* p) {
    int size = (int)sizeof( p->getCoordinates()) / 4;
    for (int i = 0; i < size; i++) {
        locs[i] = p->locs[i];
    }
}

std:: ostream& operator<<(std :: ostream& out, Coordinate& t) {
    t.printFormat(out);
    return out;
}