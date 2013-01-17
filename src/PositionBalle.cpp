#include "PositionBalle.h"

using namespace std;

PositionBalle::PositionBalle(float x, float y, float z, time_t t)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->t = t;
}

float PositionBalle::getX()
{
  return x;
}

float PositionBalle::getY()
{
  return y;
}

float PositionBalle::getZ()
{
  return z;
}

time_t PositionBalle::getT()
{
  return t;
}

void PositionBalle::setX(float x)
{
  this->x = x;
}

void PositionBalle::setY(float y)
{
  this->y = y;
}

void PositionBalle::setZ(float z)
{
  this->z = z;
}

void PositionBalle::setT(time_t t)
{
  this->t = t;
}


