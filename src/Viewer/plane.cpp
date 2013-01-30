#include "ground.h"
#include <QtOpenGL/QtOpenGL>
#include <GL/glut.h>


Ground::Ground()
{
}

void Ground::draw() {
    glBegin(GL_QUADS);
            glColor3d(1,0,0);
            glVertex3f(-1,-1,-10);
            glColor3d(1,1,0);
            glVertex3f(1,-1,-10);
            glColor3d(1,1,1);
            glVertex3f(1,1,-10);
            glColor3d(0,1,1);
            glVertex3f(-1,1,-10);
    glEnd();
}
