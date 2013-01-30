#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "tools.h"
#include <vector>
using namespace std;

class Trajectory
{
private:
    vector<Point> *_points;
    int _ID;
public:
    Trajectory();
    Trajectory(int);
    ~Trajectory();
    bool isEmpty();
    void addPoint(Point p);
    void clear();
    int getID();
    void draw();
};

#endif // TRAJECTORY_H
