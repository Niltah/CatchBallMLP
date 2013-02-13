#include "trajectory.h"

#include <QtOpenGL/QtOpenGL>
#include <GL/glut.h>
#include <vector>
#include <iostream>

Trajectory::Trajectory(int id)
{
    _ID = id;
    _points = new vector<Point>;
    r = 1;
    g = 0.8;
    b = 0;
}

Trajectory::Trajectory()
{
    _ID = 0;
    _points = new vector<Point>;
}

Trajectory::~Trajectory()
{
    delete _points;
}

bool Trajectory::isEmpty() {
    return _points->empty();
}

void Trajectory::addPoint(Point p) {
    _points->push_back(Point(p));
}

void Trajectory::clear() {
    _points->clear();
}

int Trajectory::getID() {
    return _ID;
}

void Trajectory::draw() {
    if(!isEmpty()) {
        vector<Point>::iterator i;
        glColor3f(r, g, b);
        glBegin(GL_LINE);
        for(i=_points->begin(); i<_points->end(); ++i) {
            glVertex3f(i->x, i->y, i->z);
            if(i!=_points->begin() && i!=_points->end())
                glVertex3f(i->x, i->y, i->z);
        }
        glEnd();
    }
}

void Trajectory::setColor3f(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
}
