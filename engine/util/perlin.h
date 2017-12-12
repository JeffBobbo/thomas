#ifndef PERLIN_H_INCLUDE
#define PERLIN_H_INCLUDE

#include <stdint.h>

const int P_LENGTH = 512;

class Perlin
{
  public:
    Perlin(int16_t seed);
    ~Perlin() {};

  double noise(double x, double y, double z);

  private:
    int p[P_LENGTH];
};

#endif
