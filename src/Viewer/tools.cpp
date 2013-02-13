#include "tools.h"
#include <math.h>
#ifndef M_2PI
#define M_2PI 6.283185307179586476925286766559 /* 2*pi */
#endif

Point::Point(double _x, double _y, double _z) {
    x = _x;
    y= _y;
    z = _z;
}

Point::Point() {
    Point(0, 0, 0);
}

void normalizeAngle(float &angle)
{
    while (angle < 0)
        angle += M_2PI;
    while (angle > M_2PI)
        angle -= M_2PI;
}
