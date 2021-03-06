#include <string>

struct FindResult
{
  int position = -1;
  int length = -1;
};

FindResult find(std::string source, std::string pattern)
{
  int space = 0;
  FindResult result;

  for (unsigned int s = 0; s < source.length(); s++)
  {
    for (unsigned int p = 0; p < pattern.length(); p++)
    {
      if (s + p >= source.length())
        break;

      if (pattern[p] == '~')
      {
        if (p < pattern.length() - 1)
        {
          p++;

          if (pattern[p] == '~' || pattern[p] == '*')
            return result;

          if ((space = find(source.substr(s + p + space), std::string(1, pattern[p])).position) == -1)
            break;
        }
        else
          space = source.length() - 1 - (p + s);
      }
      else if (source[s + p + space] != pattern[p] && pattern[p] != '*')
        break;

      if (p >= pattern.length() - 1)
      {
        result.position = s;
        result.length = p + space + 1;
        return result;
      }
    }
  }

  return result;
}