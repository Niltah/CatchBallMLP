#ifndef TOOLS_H
#define TOOLS_H

#include "math.h"

#define EPSILON 0.01
#define DEG2RAD (M_PI/180)
#define RAD2DEG (180/M_PI)

class Point {
public:
    Point();
    Point(double, double, double);
    double x;
    double y;
    double z;
};

#endif // TOOLS_H
