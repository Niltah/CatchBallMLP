#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "tools.h"
#include <vector>
using namespace std;

class Trajectory
{
private:
    /* TODO
    /* Ajouter éventuellement un vecteur de points supplémentaire :
    /* Un pour les points acquis par Optitrack, l'autre pour les
    /* points interpolés, après avoir fait appel à la méthode de
    /* calcul de trajectoire */
    vector<Point> *_points;
    int _ID;
    // Color
    float r;
    float g;
    float b;
public:
    Trajectory();
    Trajectory(int);
    ~Trajectory();
    bool isEmpty();
    void addPoint(Point p);
    void clear();
    int getID();
    void draw();
    void setColor3f(float r, float g, float b);
};

#endif // TRAJECTORY_H
