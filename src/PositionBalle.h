#ifndef POSITIONBALLE_H
#define POSITIONBALLE_H

#include <cstdlib>
#include <cstdio>

using namespace std;

class PositionBalle
{
 public :
  PositionBalle(float x, float y, float z, time_t t);
  
  float getX();
  float getY();
  float getZ();
  time_t getT();
  void setX(float x);
  void setY(float y);
  void setZ(float z);
  void setT(time_t t);

 protected :
  float x;
  float y;
  float z;
  time_t t;
};

#endif // POSITIONBALLE_H
