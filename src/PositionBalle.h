#ifndef POSITIONBALLE_H
#define POSITIONBALLE_H

#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

class PositionBalle
{
 public :
  PositionBalle();
  PositionBalle(vector<float> Position, time_t t);
  PositionBalle(float x, float y, float z, time_t t);
  
  ~PositionBalle();
  
  vector<float> getPosition();
  time_t getT();
  void setPosition(vector<float> Position);
  void setT(time_t t);

 protected :
  vector<float> Position; // x, y, z
  time_t t;
};

#endif // POSITIONBALLE_H
