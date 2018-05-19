#ifndef STOPWATCH_H_INCLUDE
#define STOPWATCH_H_INCLUDE

#include <stdint.h>

#include "util.h"

namespace engine
{
namespace util
{
class stopwatch_t final
{
public:
  stopwatch_t() : start(0), end(0) {}

  inline stopwatch_t& start()
  {
    start = elapsed();
    return *this;
  }

  inline stopwatch_t& end()
  {
    end = elapsed();
    return *this;
  }

  inline uint64_t getElapsedTime()
  {
    return end - start;
  }

private:
  uint64_t start;
  uint64_t end;
};
}
}

#endif
