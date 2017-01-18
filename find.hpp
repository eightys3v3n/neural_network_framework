#ifndef FIND_
#define FIND_

#include <string>

struct FindResult
{
  int position;
  int length;
};

FindResult find(std::string source, std::string pattern);

#endif // FIND_