#ifndef MATH_
#define MATH_

#include <vector>

#ifdef SFML
#include <SFML/System.hpp>
#endif // SFML

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

double radian(double degree);
double radians(double degree);
double degree(double radian);
double degrees(double radian);
double stdAngle(double x, double y);
double stdAngle(Coord one, Coord two);
long multiByteNumber(std::vector<unsigned char> input);
double sigmoid(double input, double base = 9);
double reverseSigmoid(double input, double base = 9);

#endif // MATH_