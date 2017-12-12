#include "perlin.h"

#include <cmath>

double dot(int16_t* g, double x, double y, double z)
{
  return g[0]*x + g[1]*y + g[2]*z;
}

double mix(const double a, const double b, const double t)
{
  return (1.0 - t) * a + t*b;
}

double fade(const double t)
{
  return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

double grad(const int16_t hash, const double x, const double y, const double z)
{
  const uint8_t h = hash & 15;
  const double u = h < 8 ? x : y;
  const double v = h < 4 ? y : (h==12||h==14 ? x : z);

  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

int16_t perm[] = {151,160,137,91,90,15,
  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

int16_t grad3[12][3] = {
  {1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
  {1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
  {0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1}
};

Perlin::Perlin(int16_t seed)
{
  for (int16_t i = 0; i < 256; ++i)
  {
    int16_t v;
    if (i & 1)
      v = perm[i] ^ (seed & 255);
    else
      v = perm[i] ^ ((seed >> 8) & 255);

    p[i] = p[i+256] = v;
  }
}

double Perlin::noise(double x, double y, double z)
{
  int64_t X = static_cast<int64_t>(std::floor(x));
  int64_t Y = static_cast<int64_t>(std::floor(y));
  int64_t Z = static_cast<int64_t>(std::floor(z));

  x -= X;
  y -= Y;
  z -= Z;

  X &= 255;
  Y &= 255;
  Z &= 255;

  // calculate a set of eight hashes gradient indicies
  int16_t gi000 = p[X  +p[Y  +p[Z  ]]] % 12;
  int16_t gi001 = p[X  +p[Y  +p[Z+1]]] % 12;
  int16_t gi010 = p[X  +p[Y+1+p[Z  ]]] % 12;
  int16_t gi011 = p[X  +p[Y+1+p[Z+1]]] % 12;
  int16_t gi100 = p[X+1+p[Y  +p[Z  ]]] % 12;
  int16_t gi101 = p[X+1+p[Y  +p[Z+1]]] % 12;
  int16_t gi110 = p[X+1+p[Y+1+p[Z  ]]] % 12;
  int16_t gi111 = p[X+1+p[Y+1+p[Z+1]]] % 12;

  // calculate noise contributions from each corner
  double n000 = dot(grad3[gi000], x  , y  , z  );
  double n100 = dot(grad3[gi100], x-1, y  , z  );
  double n010 = dot(grad3[gi010], x  , y-1, z  );
  double n110 = dot(grad3[gi110], x-1, y-1, z  );
  double n001 = dot(grad3[gi001], x  , y  , z-1);
  double n101 = dot(grad3[gi101], x-1, y  , z-1);
  double n011 = dot(grad3[gi011], x  , y-1, z-1);
  double n111 = dot(grad3[gi111], x-1, y-1, z-1);
  double u = fade(x);
  double v = fade(y);
  double w = fade(z);

  double nx00 = mix(n000, n100, u);
  double nx01 = mix(n001, n101, u);
  double nx10 = mix(n010, n110, u);
  double nx11 = mix(n011, n111, u);

  double nxy0 = mix(nx00, nx10, v);
  double nxy1 = mix(nx01, nx11, v);
  double nxyz = mix(nxy0, nxy1, w);

  //double r = std::sqrt(3.0) / 2.0;

  return nxyz / 1.02588;
  return nxyz;// / r;
/*
  const int16_t A = p[X  ] + Y, AA = p[A]+Z, AB = p[A+1]+Z;
  const int16_t B = p[X+1] + Y, BA = p[B]+Z, BB = p[B+1]+Z;

  return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x,   y,   z  ),
                                 grad(p[BA  ], x-1, y,   z  )),
                         lerp(u, grad(p[AB  ], x,   y-1, z  ),
                                 grad(p[BB  ], x-1, y-1, z  ))),
                 lerp(v, lerp(u, grad(p[AA+1], x,   y,   z-1),
                                 grad(p[BA+1], x-1, y,   z-1)),
                         lerp(u, grad(p[AB+1], x,   y-1, z-1),
                                 grad(p[BB+1], x-1, y-1, z-1))));
*/
}
