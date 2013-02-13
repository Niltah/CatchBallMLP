#ifndef GROUND_H
#define GROUND_H

#include "tools.h"

class Plane
{
private:
    Point tl; // Top left
    Point tr;
    Point bl;
    Point br; // Bottom right

    float r;
    float g;
    float b;
public:
    Plane(Point ptl, Point ptr, Point pbr, Point pbl);
    void draw(bool filled);
};

#endif // GROUND_H
