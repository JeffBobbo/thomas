#ifndef RANDOM_H_INCLUDE
#define RANDOM_H_INCLUDE

#include <random>

#include <stdint.h>

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

namespace thomas
{
namespace util
{
class random_t
{
public:
  random_t(const uint64_t s = 0) : mt(), seed(s)
  {
    mt.seed(s);
  }

  ~random_t() {}

  int8_t random_i8(const int8_t min, const int8_t max)
  {
    std::uniform_int_distribution<int8_t> dist(min, max);
    return dist(mt);
  }
  int16_t random_i16(const int16_t min, const int16_t max)
  {
    std::uniform_int_distribution<int16_t> dist(min, max);
    return dist(mt);
  }
  int32_t random_i32(const int32_t min, const int32_t max)
  {
    std::uniform_int_distribution<int32_t> dist(min, max);
    return dist(mt);
  }
  int64_t random_i64(const int64_t min, const int64_t max)
  {
    std::uniform_int_distribution<int64_t> dist(min, max);
    return dist(mt);
  }
  uint8_t random_u8(const uint8_t min, const uint8_t max)
  {
    std::uniform_int_distribution<uint8_t> dist(min, max);
    return dist(mt);
  }
  uint16_t random_u16(const uint16_t min, const uint16_t max)
  {
    std::uniform_int_distribution<uint16_t> dist(min, max);
    return dist(mt);
  }
  uint32_t random_u32(const uint32_t min, const uint32_t max)
  {
    std::uniform_int_distribution<uint32_t> dist(min, max);
    return dist(mt);
  }
  uint64_t random_u64(const uint64_t min, const uint64_t max)
  {
    std::uniform_int_distribution<uint64_t> dist(min, max);
    return dist(mt);
  }
  float random_f32(const float min, const float max)
  {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(mt);
  }
  double random_f64(const double min, const double max)
  {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(mt);
  }

  inline uint64_t getSeed() const { return seed; }
  //template <typename I> I random_i(const I min, const I max) const = 0;
  //template <typename R> R random_r(const R min, const R max) const = 0;
private:
  std::mt19937 mt;
  uint64_t seed;
};

/*
class random_mt : public random_t
{
public:
  random_mt(uint64_t s) : mt(), seed(s)
  {
    mt.seed(s);
  }

  template <typename I> I random_i(const I min, const I max) const
  {
    std::uniform_int_distribution<I> dist(min, max);
    return dist(mt);
  }
  template <typename R> R random_r(const R min, const R max) const
  {
    std::uniform_real_distribution<R> dist(min, max);
    return dist(mt);
  }
private:
  std::mt19937 mt;
  uint64_t seed;
};
 */
}
}

#endif
