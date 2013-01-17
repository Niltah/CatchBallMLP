#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include "PositionBalle.h"

using namespace std;

#define G_VALUE 9.81

class Trajectory
{
  // Vectorial trajectory : OM = 1/2 G t*t + A*t + B
  // g, A, B vector3d

 public:
  Trajectory();
  ~Trajectory();

  PositionBalle * getPositionBalle(time_t t);
  void computeTrajectory(PositionBalle *p1, PositionBalle *p2);

  int getComputed();
  void setComputed(int computed);
  vector<float> getA();
  vector<float> getB();
  void setA(vector<float> A);
  void setB(vector<float> B);

 protected:
  int computed;
  vector<float> A;
  vector<float> B;
};

#endif // TRAJECTORY_H
