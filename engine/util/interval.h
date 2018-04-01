#ifndef INTERVAL_H_INCLUDE
#define INTERVAL_H_INCLUDE

#include "util.h"

class interval_t final
{
public:
  /**
   * Default constructor, constructs an off interval of no duration
   */
  interval_t() : start(-1), duration(0) {};
  /**
   * Constructs an interval d ms, starting immediately
   */
  interval_t(const millis_t d) : start(::ticks()), duration(d) {};
  ~interval_t() {};

  /**
   * Sets the interval of this interval to the desired length in milliseconds.
   * Does not effect the starting time
   * @param millis Length of duration in milliseconds
   */
  inline void setMillis(const millis_t millis) { duration = millis; }
  /**
   * Sets the interval of this interval to the desired length in seconds.
   * Does not effect the starting time
   * @param millis Length of duration in seconds
   */
  inline void setSeconds(const millis_t seconds) { duration = seconds * 1000; }

  /**
   * Turns off the interval
   */
  inline void turnOff() { start = -1; }
  /**
   * Turns on the interval
   * Can be called on a running interval to reset the start time
   */
  inline void turnOn() { start = ::ticks(); }
  /**
   * Advances the interval by count durations
   * Use this in combination with ticks() to advance the interval when needed
   * @param count The number of ticks to advance by
   */
  inline void advance(const int count) { start += count * duration; }

  /**
   * @return True if this interval is on
   */
  inline bool isOn() const { return start != -1; }
  /**
   * @return True if this interval is off
   */
  inline bool isOff() const { return start == -1; }
  /**
   * @return True if this interval has had at least one tick elapse
   */
  inline bool isTime() const { return ::ticks() > start + duration; }
  /**
   * @return The number of milliseconds remaining until the next tick
   */
  inline millis_t timeRemaining() const { return start + duration - ::ticks(); }
  /**
   * @return The number of ticks, or times this interval has elapsed, since the start
   */
  inline int ticks() const { return static_cast<int>((::ticks() - start) / duration); }
  /**
   * @return The progress made towards the next tick, can be greater than 1
   */
  inline double progress() const { return static_cast<double>(ticks() - start) / static_cast<double>(duration); }

private:
  millis_t start;
  millis_t duration;
};

#endif
