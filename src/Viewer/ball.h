#ifndef BALL_H
#define BALL_H

class Ball
{
private:
    // Position
    float x;
    float y;
    float z;

    // Color
    float r;
    float g;
    float b;

    float radius;
public:
    Ball();
    Ball(float px, float py, float pz, float bradius);
    void updatePosition(float px, float py, float pz);
    void setRadius(float bradius);
    void setColor3f(float r, float g, float b);
    void draw();
};

#endif // BALL_H
