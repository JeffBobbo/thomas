#include "util.h"
#include "../internal.h"

millis_t tStart;
millis_t tElapsed;
millis_t tLast;
millis_t tDelta;
uint32_t frames;
millis_t fpsTime;
double cfps;

millis_t start()
{
  return tStart;
}

millis_t elapsed()
{
  return ticks() - tStart;
}

millis_t last()
{
  return tLast;
}

millis_t delta()
{
  return tDelta;
}

void initTicks()
{
  tStart = ticks();
  tDelta = 0;
  tLast = tStart;
  frames = 0;
  fpsTime = tStart;
  cfps = 0.0;
}

void updateTicks()
{
  millis_t now = ticks();
  tDelta = now - tLast;
  tLast = now;
  ++frames;
  if (now - fpsTime > 1000)
  {
    cfps = static_cast<double>(frames) / ((now - fpsTime) / 1000.0);
    fpsTime += 1000;
    frames = 0;
  }
}

double fps()
{
  return cfps;
}
