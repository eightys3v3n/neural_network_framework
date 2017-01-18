#include <iostream>
#include "findTest.hpp"
#include "neuronTest.hpp"
using namespace std;

int main()
{
  try
  {
    findTest();
    cout << "findTest passed" << endl;
  }
  catch ( string *error )
  {
    cout << "findTest: " << *error << endl;
    return true;
  }

  try
  {
    neuronTest();
    cout << "neuronTest passed" << endl;
  }
  catch ( string *error )
  {
    cout << "neuronTest: " << *error << endl;
    return true;
  }

  return false;
}