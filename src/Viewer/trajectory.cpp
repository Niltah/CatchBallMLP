#include "trajectory.h"

#include <QtOpenGL/QtOpenGL>
#include <GL/glut.h>
#include <vector>
#include <iostream>

Trajectory::Trajectory(int id)
{
    _ID = id;
    _points = new vector<Point>;
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
        glColor3f(1, 0.82, 0);
        glBegin(GL_LINE_LOOP);
        for(i=_points->begin(); i<_points->end(); ++i) {
            glVertex3f(i->x, i->y, i->z);
        }
        glEnd();
    }
}
