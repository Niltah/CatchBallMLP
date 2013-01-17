#include "Trajectory.h"

using namespace std;

Trajectory::Trajectory()
{
  computed = 0;
  
  A.push_back(0);
  A.push_back(0);
  A.push_back(0);

  B.push_back(0);
  B.push_back(0);
  B.push_back(0);
}

Trajectory::~Trajectory()
{
  A.clear();
  B.clear();
}

PositionBalle * Trajectory::getPositionBalle(time_t t)
{
  if(!computed)
    {
      cout << "Trying to predict position before computing trajectory, operation aborted'" << endl;
      return new PositionBalle();
    }
  else
    {
      float x = A[0]*t + B[0];
      float y = A[1]*t + B[1];
      float z = -(G_VALUE*t*t/2) + A[2]*t + B[2];

      return new PositionBalle(x, y, z, t);      
    }
}

void Trajectory::computeTrajectory(PositionBalle *p1, PositionBalle *p2)
{
  time_t t1 = p1->getT();
  time_t t2 = p2->getT();

  if(t1 == t2)
    cout << "The two given positions have the same date, operation aborted" << endl;
  else if(t1 == -1 || t2 == -1)
    cout << "One of the given positions isn't properly set, operation aborted" << endl;
  else
    {
      vector<float> P1 = p1->getPosition();
      float x1 = P1[0];
      float y1 = P1[1];
      float z1 = P1[2];  
  
      vector<float> P2 = p2->getPosition();
      float x2 = P2[0];
      float y2 = P2[1];
      float z2 = P2[2];

      A.push_back((x2-x1)/(t2-t1));
      B.push_back(x1-A[0]*t1);

      A.push_back((y2-y1)/(t2-t1));
      B.push_back(y1-A[1]*t1);

      float Z1 = z1 + (G_VALUE*t1*t1/2);
      float Z2 = z2 + (G_VALUE*t2*t2/2);

      A.push_back((Z2-Z1)/(t2-t1));
      B.push_back(Z1-A[2]*t1);

      computed = 1;
    }
}

int Trajectory::getComputed()
{
  return computed;
}

void Trajectory::setComputed(int computed)
{
  this->computed = computed;
}

vector<float> Trajectory::getA()
{
  return A;
}

vector<float> Trajectory::getB()
{
  return B;
}

void Trajectory::setA(vector<float> A)
{
  this->A = A;
}

void Trajectory::setB(vector<float> B)
{
  this->B = B;
}
