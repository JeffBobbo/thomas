#include <util/colour.h>

ARGB::operator HSVA() const
{
  HSVA out;
  out.a = a;

  double min = std::min(std::min(r, g), b);
  double max = std::max(std::max(r, g), b);
  double delta = max - min;
  out.v = max;

  if (delta < 0.00001)
  {
    out.s = 0.0;
    out.h = angle_t::degrees(0.0);
    return out;
  }

  if (max > 0.0)
  {
    out.s = delta / max;
  }
  else
  {
    out.s = 0.0;
    out.h = angle_t::degrees(0.0);
    return out;
  }

  if (r >= max)
    out.h = angle_t::degrees(60.0 * (g - b) / delta);
  else if (g >= max)
    out.h = angle_t::degrees(120.0 + 60.0 * (b - r) / delta);
  else
    out.h = angle_t::degrees(240.0 + 60.0 * (r - g) / delta);

  out.h %= angle_t::degrees(360.0);

  return out;
}

HSVA::operator ARGB() const
{
  if (s <= 0.0)
    return ARGB(a, v, v, v);

  double hh = std::fmod(h.degrees(), 360.0) / 60.0;
  int i = static_cast<int>(std::floor(hh));
  double ff = hh - i;
  double p = v * (1.0 - s);
  double q = v * (1.0 - (s * ff));
  double t = v * (1.0 - (s * (1.0 - ff)));

  switch(i)
  {
    case 0:
      return ARGB(a, v, t, p);
    case 1:
      return ARGB(a, q, v, p);
    case 2:
      return ARGB(a, p, v, t);
    case 3:
      return ARGB(a, p, q, v);
    case 4:
      return ARGB(a, t, p, v);
    case 5:
      return ARGB(a, v, p, q);
  }
  return ARGB(a, 0.0, 0.0, 0.0);
}
