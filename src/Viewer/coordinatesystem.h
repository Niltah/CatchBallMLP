#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

/*
   This class represents the coordinate system of the scene.
   It allows not to use the openGL coordinate system as the
   coordinate system of the scene.
*/

class CoordinateSystem
{
private:
    // Coordinates of the Scene coordinate system in the OpenGL coordinate system
    float x;
    float y;
    float z;
    int xRot;
    int yRot;
    int zRot;
    bool inSceneCS;
    void qNormalizeAngle(int &angle);
    void drawCS(float val);
public:
    CoordinateSystem();
    void moveCoordinateSystem(float csx, float csy, float csz);
    void rotateCoordinateSystem(int csxr, int csyr, int cszr);
    void loadSceneCS();
    void loadglCS();
    void displayGlCS();
    void displaySceneCS();
};

#endif // COORDINATESYSTEM_H
