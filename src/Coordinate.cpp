#include "Coordinate.h"
#include "Point.h"

/*
 * allows any function to request an objects location,
 * without having to know how many coordinates it contains
 * (ie, which dimension it is in)
 */
int Coordinate::getNextCoordinate(int place) {
    return locs[place];
}
/*
 * Copies the coordinates from one point to another
 */
Coordinate::Coordinate(Coordinate* p) {
    int size = (int)sizeof( p->getCoordinates()) / 4;
    for (int i = 0; i < size; i++) {
        locs[i] = p->locs[i];
        cout << "CREATE COORDINATE: " << p->locs[i] << endl;
    }
}

std:: ostream& operator<<(std :: ostream& out, Coordinate& t) {
    t.printFormat(out);
    //out << "("<< t.locs[0] << "," << t.locs[1] << ")"<<endl;
    return out;
}



/*
 * Returns a generic Coordinate with the locations of
 * the Point.
 */
int* Coordinate::getCoordinates() {
    cout << "LOCS FULL? " << locs[0] << "," << locs[1] << endl;
    return locs;
}
Coordinate* Coordinate::getMyLocation() {
    Point* p = new Point(locs[0], locs[1]);
    return p;
}