#ifndef MGI_H
#define MGI_H

#include <cstdlib>
#include <cstdio>
#include <vector>

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

#define THETA3VALUE 0

using namespace std;

class Mgi
{
 public :
  Mgi();
  ~Mgi();

  float getTheta1();
  float getTheta2();
  float getTheta3();
  float getTheta4();
  float getTheta5();
  float getTheta6();
  float getTheta7();

  float radianToDegree(float theta);

  int testAngleValue(float theta, int i);

 protected :
  float d1;
  float d3;
  float d5;
  float a6;
  float a7;

  float xp;
  float yp;
  float zp;
  float xxd;
  float yxd;
  float zxd;
  float xyd;
  float yyd;
  float zyd;
  float xzd;
  float yzd;
  float zzd;

  float theta1;
  float theta2;
  float theta3;
  float theta4;
  float theta5;
  float theta6;
  float theta7;

  vector<double> max_val;
  vector<double> min_val;
};

#endif // MGI_H
