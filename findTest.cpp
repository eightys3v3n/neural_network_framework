#include <string>
#include "find.hpp"

bool findTestStatus = false;

bool findTest()
{
  if ( findTestStatus )
    return false;

  FindResult result;
  std::string input = "abcdefghijklmnopqrstuvwxyz";

  result = find(input, "abc");
  if (result.position != 0)
  {
    throw new std::string("'abc' position failed");
    return true;
  }

  if (result.length != 3)
  {
    throw new std::string("'abc' length failed");
    return true;
  }

  result = find(input, "xyz");
  if (result.position != 23)
  {

    throw new std::string("'xyz' position failed");
    return true;
  }

  if (result.length != 3)
  {
    throw new std::string("'xyz' length failed");
    return true;
  }

  result = find(input, "a*c");
  if (result.position != 0)
  {
    throw new std::string("'a*c' position failed");
    return true;
  }

  if (result.length != 3)
  {
    throw new std::string("'a*c' length failed");
    return true;
  }

  result = find(input, "x*z");
  if (result.position != 23)
  {
    throw new std::string("'x*z' position failed");
    return true;
  }

  if (result.length != 3)
  {
    throw new std::string("'x*z' length failed");
    return true;
  }

  result = find(input, "a~c");
  if (result.position != 0)
  {
    throw new std::string("'a~c' position failed");
    return true;
  }

  if (result.length != 3)
  {
    throw new std::string("'a~c' length failed");
    return true;
  }

  result = find(input, "x~z");
  if (result.position != 23)
  {
    throw new std::string("'x~z' position failed");
    return true;
  }

  if (result.length != 3)
  {
    throw new std::string("'x~z' length failed");
    return true;
  }

  result = find(input, "a~d");
  if (result.position != 0)
  {
    throw new std::string("'a~d' position failed");
    return true;
  }

  if (result.length != 4)
  {
    throw new std::string("'a~d' length failed");
    return true;
  }

  result = find(input, "w~z");
  if (result.position != 22)
  {
    throw new std::string("'w~z' position failed");
    return true;
  }

  if (result.length != 4)
  {
    throw new std::string("'w~z' length failed");
    return true;
  }

  findTestStatus = true;
  return false;
}