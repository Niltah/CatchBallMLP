#include "coordinatesystem.h"
#include <QtOpenGL/QtOpenGL>
#include "glwidget.h"

void CoordinateSystem::qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


CoordinateSystem::CoordinateSystem()
{
    inSceneCS = false;
    x = 0;
    y = 0;
    z = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

void CoordinateSystem::moveCoordinateSystem(float csx, float csy, float csz) {
    bool isSCS = inSceneCS;
    loadglCS();

    x = csx;
    y = csy;
    z = csz;

    if(isSCS)
        loadSceneCS();
}

void CoordinateSystem::rotateCoordinateSystem(int csxr, int csyr, int cszr) {
    bool isSCS = inSceneCS;
    loadglCS();

    xRot = csxr;
    yRot = csyr;
    zRot = cszr;

    qNormalizeAngle(xRot);
    qNormalizeAngle(yRot);
    qNormalizeAngle(zRot);

    if(isSCS)
        loadSceneCS();
}

void CoordinateSystem::loadSceneCS() {
    if(inSceneCS) return;

    inSceneCS = true;
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glTranslatef(x, y, z);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
}

void CoordinateSystem::loadglCS() {
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    inSceneCS = false;
}

void CoordinateSystem::displayGlCS() {
    bool isSCS = inSceneCS;
    loadglCS();

    drawCS(0.05);

    if(isSCS)
        loadSceneCS();
}

void CoordinateSystem::displaySceneCS() {
    bool isSCS = inSceneCS;
    loadSceneCS();

    drawCS(0.3);

    if(!isSCS)
        loadglCS();
}

void CoordinateSystem::drawCS(float val) {
    // PRIVATE METHOD!!
    // Should not be used by other methods than displayGLCS and displaySceneCS
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(-0.1*val, 0, 0);
    glVertex3f(val, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, -0.1*val, 0);
    glVertex3f(0, val, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -0.1*val);
    glVertex3f(0, 0, val);
    glEnd();
}
