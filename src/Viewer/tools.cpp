#include "tools.h"


Point::Point(double _x, double _y, double _z) {
    x = _x;
    y= _y;
    z = _z;
}

Point::Point() {
    Point(0, 0, 0);
}
