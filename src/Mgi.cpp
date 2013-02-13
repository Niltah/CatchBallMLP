#include <cmath>
#include <iostream>
#include "Equations_de_paul.h"
#include "Mgi.h"

using namespace std;

/*
Toutes les valeurs ainsi déterminées le sont pour l'instant à une constante près
 */

Mgi::Mgi()
{
  d1 = 0;
  d3 = 26.5;
  d5 = 25.5;
  a6 = 0;
  a7 = -9;
}

Mgi::~Mgi()
{
  max_val.clear();
  min_val.clear();
}

float Mgi::getTheta1(){
  float theta1;
  struct_type_2 S;

  float X = xp - (a7*xxd);
  float Y = (a7*yxd) - yp;
  float Z = d5 * sin(theta3) * sin(theta4);
  
  if(!solve_type_2(&S, X, Y, Z))
    {
      cout << "Pas de solution" << endl;
      return 0;
    }

  theta1 = radianToDegree(S.Ai[0]);

  if(!testAngleValue(theta1, 1))
    theta1 = radianToDegree(S.Ai[1]);  

  return theta1; // TODO theta1 + cte1
}

float Mgi::getTheta2()
{
  return 1;
}

float Mgi::getTheta3()
{
  float theta3 = THETA3VALUE;
  
  return theta3;
}

float Mgi::getTheta4()
{
  float theta4;
  
  theta4 = 2*asin((sqrt(pow((xp - a7*xxd), 2)+pow((yp - a7*yxd), 2)+pow((zp - a7*zxd) , 2)))/(2*d5));

  theta4 = radianToDegree(theta4);

  //  if(!testAngleValue(theta4, 4))
  //theta4 = 180-theta4;

  return theta4;
}

float Mgi::getTheta5()
{
  return 1;
}

float Mgi::getTheta6()
{
  return 1;
}

float Mgi::getTheta7()
{
  return 1;
}


float Mgi::radianToDegree(float theta)
{
  return(theta*180/M_PI);
}


int Mgi::testAngleValue(float theta, int i)
{
  return(theta > min_val[i] && theta < max_val[i]);
}
