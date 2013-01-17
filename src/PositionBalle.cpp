#include <iostream>
#include "PositionBalle.h"

using namespace std;

PositionBalle::PositionBalle()
{
  this->Position.push_back(0);
  this->Position.push_back(0);
  this->Position.push_back(0);
  this->t = -1;
}

PositionBalle::PositionBalle(vector<float> Position, time_t t)
{
  if(Position.size() == 3)
    this->Position = Position;
  else
    {
      cout << "Invalid position vector, operation aborted" << endl;
      this->Position.push_back(0);
      this->Position.push_back(0);
      this->Position.push_back(0);
    }
  this->t = t;
}

PositionBalle::PositionBalle(float x, float y, float z, time_t t)
{
  this->Position.push_back(x);
  this->Position.push_back(y);
  this->Position.push_back(z);
  this->t = t;
}

PositionBalle::~PositionBalle()
{
  Position.clear();
}

vector<float> PositionBalle::getPosition()
{
  return Position;
}

time_t PositionBalle::getT()
{
  return t;
}

void PositionBalle::setPosition(vector<float> Position)
{
  if(Position.size() == 3)
    this->Position = Position;
  else
      cout << "Invalid position vector, operation aborted" << endl;
}

void PositionBalle::setT(time_t t)
{
  this->t = t;
}


