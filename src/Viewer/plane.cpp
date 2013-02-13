#include "plane.h"
#include <QtOpenGL/QtOpenGL>
#include <GL/glut.h>
#include <iostream>

Plane::Plane(Point ptl, Point ptr, Point pbr, Point pbl)
{
    tl = ptl;
    tr = ptr;
    bl = pbl;
    br = pbr;

    r = 0.55;
    g = 0.55;
    b = 0.55;
}

void Plane::draw(bool filled) {
    if(filled) {
        glBegin(GL_QUADS);
                glColor3d(r, g, b);
                glVertex3f(tl.x, tl.y, tl.z);
                glVertex3f(tr.x, tr.y, tr.z);
                glVertex3f(br.x, br.y, br.z);
                glVertex3f(bl.x, bl.y, bl.z);
        glEnd();
    }
    else {
        glBegin(GL_LINES);
        glColor3d(r, g, b);
        for(float i=tl.x; i<=tr.x; i+=0.02) {
            glVertex3f(i, tl.y, tl.z);
            glVertex3f(i, bl.y, tl.z);
        }
        for(float i=tl.y; i<=bl.y; i+=0.02) {
            glVertex3f(tl.x, i, tl.z);
            glVertex3f(tr.x, i, tl.z);
        }
        glEnd();
    }
}

//void Plane::draw() {
//    glBegin(GL_QUADS);
//            glColor3d(1,0,0);
//            glVertex3f(-1,-1,-10);
//            glColor3d(1,1,0);
//            glVertex3f(1,-1,-10);
//            glColor3d(1,1,1);
//            glVertex3f(1,1,-10);
//            glColor3d(0,1,1);
//            glVertex3f(-1,1,-10);
//    glEnd();
//}
