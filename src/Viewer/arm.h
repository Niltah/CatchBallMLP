#ifndef ARM_H
#define ARM_H
#include <math.h>

#define INIT_THETA1 0
#define INIT_THETA2 0
#define INIT_THETA3 0
#define INIT_THETA4 0
#define INIT_THETA5 0
#define INIT_THETA6 0
#define INIT_THETA7 0
#define INIT_L1 2.00
#define INIT_L2 1.60

class Arm
{
private:
    float theta[7];
    float l1;
    float l2;
    float base_x;
    float base_y;
    float base_z;
    float staticRotation[7]; // Set the correspondance arm angles <=> viewer angles

public:
    Arm(float basex, float basey, float basez);
    void draw();
    void setAngleRad(int numAngle, float valAngle); // Set angle number numAngle to valAngle radians
    float getAngleRad(int numAngle);
};

#endif // ARM_H
