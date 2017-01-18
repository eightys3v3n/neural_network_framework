#include <cmath>
#include <vector>

#ifdef SFML
#include <SFML/System.hpp>
#endif // SFML

//#include "find.hpp"

struct Coord
{
  Coord(double newX, double newY) : x(newX), y(newY) {}
  Coord() : x(0), y(0) {}

  double x;
  double y;
};

struct Displacement
{
  #ifdef SFML
  Displacement(sf::Vector2f one, sf::Vector2f two);
  #endif // SFML

  Displacement(Coord one, Coord two);
  Displacement();

  double x;
  double y;
  double angle;
  double distance;
};

double radian(double degree) { return degree * 3.14159265358979323846 / 180.0; }
double radians(double degree) { return radian(degree); }
double degree(double radian) { return radian * 180.0 / 3.14159265358979323846; }
double degrees(double radian) { return degree(radian); }

double stdAngle(double x, double y)
{
  double angle;

  angle = degree(atan( y / x ));

  if (x != 0 && y != 0)
  {
    if (x > 0)
    {
      if (y < 0)
        angle += 360;
    }
    else
    {
      if (y > 0)
        angle += 180;
      else
        angle += 180;
    }
  }
  else
  {
    if (y == 0 && x == 0)
      angle = 0;
    else if (x == 0)
    {
      if (y > 0)
        angle = 90;
      else
        angle = 270;
    }
    else
    {
      if (x > 0)
        angle = 0;
      else
        angle = 180;
    }
  }

  return angle;
}
double stdAngle(Coord one, Coord two) { return stdAngle(two.x - one.x, two.y - one.y); }

#ifdef SFML
Displacement::Displacement(sf::Vector2f vone, sf::Vector2f vtwo)
{
  Coord one(vone.x, vone.y);
  Coord two(vtwo.x, vtwo.y);

  x = two.x - one.x;
  y = two.y - one.y;
  angle = stdAngle(one, two);

  distance = sqrt( pow(x, 2) + pow(y, 2) );
}
#endif // SFML

Displacement::Displacement(Coord one, Coord two)
{
  x = two.x - one.x;
  y = two.y - one.y;
  angle = stdAngle(one, two);

  distance = sqrt( pow(x, 2.0) + pow(y, 2.0) );
}

Displacement::Displacement()
{
  x = 0;
  y = 0;
  angle = 0;
  distance = 0;
}

long multiByteNumber(std::vector<unsigned char> input)
{
  long output = 0;

  if (input.size() > 64)
    return 0;

  for (unsigned int p = 0; p < input.size(); p++)
    output += input[p] * pow(256, p);

  return output;
}

double sigmoid(double input, double base)
{
  long double result = 0;
  long long buffer = 0;

  result = (2 / (1 + pow(base, input))) - 1;

  buffer = result * 1e15;
  result = buffer / 1e15;

  return result;
}

double reverseSigmoid(double input, double base)
{
  long double result = 0;
  long long buffer = 0;

  result = log10((2 / (input + 1)) - 1) / log10(base);

  buffer = result * 1e15;
  result = buffer / 1e15;

  return result;
}