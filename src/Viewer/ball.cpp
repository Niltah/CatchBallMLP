#include "ball.h"
#include <GL/glut.h>

Ball::Ball(float px, float py, float pz, float bradius)
{
    x = px;
    y = py;
    z = pz;
    radius = bradius;
    r = 1;
    g = 1;
    b = 1;
}

Ball::Ball() {
    Ball(0, 0, 0, 0.05);
}

void Ball::updatePosition(float px, float py, float pz) {
    x = px;
    y = py;
    z = pz;
}

void Ball::setRadius(float ball_radius) {
    radius = ball_radius;
}

void Ball::setColor3f(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
}

void Ball::draw() {
    glColor3f(r,g,b);
    GLfloat mshin[] = {5.0};
    GLfloat mspec[] = {0.5,0.5,0.5,1.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, mshin);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mspec);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(radius, radius, radius);
    glutSolidSphere(1.0,16,16);
    glPopMatrix();
}
