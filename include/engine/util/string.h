#ifndef STRING_H_INCLUDE
#define STRING_H_INCLUDE

#include <algorithm> // std::transform
#include <string> // toupper, tolower

#include <cctype>

namespace engine
{
namespace util
{
inline void toUpper(std::string& s)
{
  std::transform(s.begin(), s.end(), s.begin(), toupper);
}
inline void toLower(std::string& s)
{
  std::transform(s.begin(), s.end(), s.begin(), tolower);
}

std::string commify(const int64_t n)
{
  bool neg = n < 0;
  std::string s = std::to_string(std::abs(n));
  const std::string::size_type len = s.length();
  std::string::size_type pos = (len % 3);
  while (pos != 0 && pos < len)
  {
    s.replace(pos, 0, 1, ',');
    pos += 4;
  }
  return neg ? "-" + s : s;
}
}
}

#endif
