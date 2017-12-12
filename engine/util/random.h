#ifndef RANDOM_H_INCLUDE
#define RANDOM_H_INCLUDE

#include <random>

void seed(uint64_t s = 0);

std::mt19937& getMT();

template <typename T> inline T random(const T min, const T max)
{
  std::uniform_int_distribution<T> dist(min, max);
  return dist(getMT());
}
template <> inline float random<float>(const float min, const float max)
{
  std::uniform_real_distribution<float> dist(min, max);
  return dist(getMT());
}
template <> inline double random<double>(const double min, const double max)
{
  std::uniform_real_distribution<double> dist(min, max);
  return dist(getMT());
}

bool inline randomBool()
{
  static std::uniform_int_distribution<int> dist(0, 1);
  return dist(getMT());
}

#endif
