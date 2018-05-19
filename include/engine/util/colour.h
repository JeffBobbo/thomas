#ifndef ARGB_H_INCLUDE
#define ARGB_H_INCLUDE

#include "angle.h"
#include "../util/util.h"

struct HSVA;

struct ARGB
{
  double a, r, g, b;

  ARGB() : a(1.0), r(1.0), g(1.0), b(1.0) {}
  ARGB(const double alpha, const double red, const double green, const double blue)
   : a(alpha), r(red), g(green), b(blue) {}
  ARGB(const uint8_t alpha, const uint8_t red, const uint8_t green, const uint8_t blue)
   : a(alpha/255.0), r(red/255.0), g(green/255.0), b(blue/255.0) {}
  ARGB(const ARGB& cp) : a(cp.a), r(cp.r), g(cp.g), b(cp.b) {}
  ARGB(ARGB&& mv) : a(mv.a), r(mv.r), g(mv.g), b(mv.b) {}

  inline ARGB& operator=(const ARGB& assign)
  {
    a = assign.a;
    r = assign.r;
    g = assign.g;
    b = assign.b;
    return *this;
  }
  inline ARGB& operator=(ARGB&& assign)
  {
    a = assign.a;
    r = assign.r;
    g = assign.g;
    b = assign.b;
    return *this;
  }

  inline bool operator==(const ARGB& rhs)
  {
    return a == rhs.a &&
           r == rhs.r &&
           g == rhs.g &&
           b == rhs.b;
  }

  ARGB interpolate(const ARGB& c, const double p) const
  {
    return ARGB(
      lerp(a, c.a, p),
      lerp(r, c.r, p),
      lerp(g, c.g, p),
      lerp(b, c.b, p));
  }

  operator HSVA() const;
};

struct HSVA
{
  angle_t h;
  double s, v, a;

  HSVA() : h(), s(1.0), v(1.0), a(1.0) {}
  HSVA(const angle_t hue, const double saturation, const double value, const double alpha)
   : h(hue), s(saturation), v(value), a(alpha) {}
  HSVA(const HSVA& cp) : h(cp.h), s(cp.s), v(cp.v), a(cp.a) {}
  HSVA(HSVA&& mv) : h(std::move(mv.h)), s(mv.s), v(mv.v), a(mv.a) {}

  inline HSVA& operator=(const HSVA& assign)
  {
    h = assign.h;
    s = assign.s;
    v = assign.v;
    a = assign.a;
    return *this;
  }
  inline HSVA& operator=(HSVA&& assign)
  {
    h = std::move(assign.h);
    s = assign.s;
    v = assign.v;
    a = assign.a;
    return *this;
  }

  inline bool operator==(const HSVA& rhs)
  {
    return h == rhs.h &&
           s == rhs.s &&
           v == rhs.v &&
           a == rhs.a;
  }

  HSVA interpolate(const HSVA& c, const double p) const
  {
    return HSVA(
      lerp(h, c.h, p),
      lerp(s, c.s, p),
      lerp(v, c.v, p),
      lerp(a, c.a, p));
  }

  operator ARGB() const;
};



#endif
