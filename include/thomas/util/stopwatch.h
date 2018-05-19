#ifndef STOPWATCH_H_INCLUDE
#define STOPWATCH_H_INCLUDE

#include <stdint.h>

#include "util.h"

namespace thomas
{
namespace util
{
/**
 * stopwatch_t can be used as a stopwatch with millisecond precision
 */
class stopwatch_t final
{
public:
  stopwatch_t() : start(0), end(0) {}

  /**
   * Starts the stopwatch
   * @return reference to the stopwatch
   */
  inline stopwatch_t& start()
  {
    start = elapsed();
    return *this;
  }

  /**
   * Stops the stopwatch
   * @return reference to the stopwatch
   */
  inline stopwatch_t& end()
  {
    end = elapsed();
    return *this;
  }

  /**
   * Gets the amount of time currently counted by the stop watch
   * @return The time in milliseconds
   */
  inline uint64_t getElapsedTime()
  {
    return elapsed() - start;
  }

  /**
   * Gets the amount of time recorded by the stop watch
   * @return The time in milliseconds
   */
  inline uint64_t getTime()
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
