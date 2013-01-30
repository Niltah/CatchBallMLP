#include "arm.h"
#include "tools.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

Arm::Arm(float basex, float basey, float basez)
{
    base_x = basex;
    base_y = basey;
    base_z = basez;

    l1 = 2.0;
    l2 = 1.5;

    // Initial position for each servo (in degrees*60)
    staticRotation[0] = -45;
    staticRotation[1] = 0;
    staticRotation[2] = 0;
    staticRotation[3] = 0;
    staticRotation[4] = 0;
    staticRotation[5] = 0;
    staticRotation[6] = 0;

    theta[0] = staticRotation[0];
    theta[1] = staticRotation[1];
    theta[2] = staticRotation[2];
    theta[3] = staticRotation[3];
    theta[4] = staticRotation[4];
    theta[5] = staticRotation[5];
    theta[6] = staticRotation[6];

}

void Arm::draw() {
    /* TO BE CONTINUED... */
    glPushMatrix();
    glTranslatef(base_x, base_y, base_z);
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(abs(l1*sin(theta[0])), l1*cos(theta[0]), 0);
/*
    glColor3f(0, 1, 0);
    glVertex3f(-0.1*val, 0, 0);
    glVertex3f(val, 0, 0);
*/
    glEnd();
    glPopMatrix();
}

void Arm::setAngleRad(int numAngle, float valAngle) {
    if(numAngle<1 || numAngle>7) {
        cerr << "Incorrect angle theta " << numAngle << endl;
        return;
    }
    theta[numAngle-1] = staticRotation[numAngle-1] + valAngle;
    normalizeAngle(theta[numAngle-1]);

}

float Arm::getAngleRad(int numAngle) {
    if(numAngle<1 || numAngle>7) {
        cerr << "Incorrect angle theta " << numAngle << endl;
        return 0;
    }
    return  theta[numAngle-1] - staticRotation[numAngle-1];
}
