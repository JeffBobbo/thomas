#ifndef ANGLE_H_INCLUDE
#define ANGLE_H_INCLUDE

#include <cmath>
#include <iostream>

#ifdef _WIN32
static inline double pi()
{
  static const double p = std::atan2(0.0, -1.0);
  return p;
}
#else
constexpr double pi()
{
  return std::atan2(0.0, -1.0);
}
#endif

class angle_t final
{
private:
  double value;

  angle_t(double d) : value(d) {}

public:
  /**
   * Default constructor, constructs an angle of 0
   */
  angle_t() : value(0.0) {}

  /**
   * Copy constructor, creates a new angle_t that is equal to copy
   */
  angle_t(const angle_t& copy) : value(copy.value) {}

  /**
   * Creates an instance of an angle_t that has d degrees
   * @param  d number of degrees
   * @return   angle_t instance
   */
  static angle_t degrees(const double d) { return angle_t(d * pi() / 180.0); }
  /**
   * Creates an instance of an angle_t that has r radians
   * @param  r number of radians
   * @return   angle_t instance
   */
  static angle_t radians(const double r) { return angle_t(r); }

  inline angle_t& operator=(const angle_t& assign)
  {
    value = assign.value;
    return *this;
  }

  inline angle_t operator-() const
  {
    return angle_t(-value);
  }

  inline angle_t operator+(const angle_t& rhs) const
  {
    return angle_t(value + rhs.value);
  }
  inline angle_t operator-(const angle_t& rhs) const
  {
    return angle_t(value - rhs.value);
  }
  inline angle_t operator*(const angle_t& rhs) const
  {
    return angle_t(value * rhs.value);
  }
  inline angle_t operator*(const double rhs) const
  {
    return angle_t(value * rhs);
  }
  inline angle_t operator/(const angle_t& rhs) const
  {
    return angle_t(value / rhs.value);
  }
  inline angle_t operator/(const double rhs) const
  {
    return angle_t(value / rhs);
  }
  /**
   * Performs doubleing point modulo
   */
  inline angle_t operator%(const angle_t& rhs) const
  {
    return angle_t(std::fmod(value, rhs.value));
  }

  inline angle_t& operator+=(const angle_t& rhs)
  {
    value += rhs.value;
    return *this;
  }
  inline angle_t& operator-=(const angle_t& rhs)
  {
    value -= rhs.value;
    return *this;
  }
  inline angle_t& operator*=(const angle_t& rhs)
  {
    value *= rhs.value;
    return *this;
  }
  inline angle_t& operator*=(const double rhs)
  {
    value *= rhs;
    return *this;
  }
  inline angle_t& operator/=(const angle_t& rhs)
  {
    value /= rhs.value;
    return *this;
  }
  inline angle_t& operator/=(const double rhs)
  {
    value /= rhs;
    return *this;
  }
  /**
   * Performs doubleing point modulo
   */
  inline angle_t& operator%=(const angle_t& rhs)
  {
    value = std::fmod(value, rhs.value);
    return *this;
  }

  /**
   * Returns the number of radians represented by this angle_t
   * @return Radians
   */
  inline double radians() const { return value; }
  /**
   * Returns the number of degrees represented by this angle_t
   * @return Degrees
   */
  inline double degrees() const { return value * 180.0 / pi(); }

  /**
   * Returns the absolute value of the supplied angle
   */
  inline static angle_t abs(const angle_t& a) { return angle_t(std::abs(a.value)); }

  /**
   * Computes the sine of an angle
   * @param  a The angle to compute for
   * @return
   */
  inline static double sin(const angle_t& a) { return std::sin(a.value); }
  /**
   * Computes the cosine of an angle
   * @param  a The angle to compute for
   * @return
   */
  inline static double cos(const angle_t& a) { return std::cos(a.value); }
  /**
   * Computes the tangent of an angle
   * @param  a The angle to compute for
   * @return
   */
  inline static double tan(const angle_t& a) { return std::tan(a.value); }
  /**
   * Computes arc sine of a
   * @param  The arc sine of a
   * @return
   */
  inline static angle_t asin(const double a) { return angle_t(std::asin(a)); }
  /**
   * Computes arc cosine of a
   * @param  The arc cosine of a
   * @return
   */
  inline static angle_t acos(const double a) { return angle_t(std::acos(a)); }
  /**
   * Computes arc tangent of a
   * @param  The arc tangent of a
   * @return
   */
  inline static angle_t atan(const double a) { return angle_t(std::atan(a)); }
  /**
   * Computes arc tanget of x and y
   * @param  y
   * @param  x
   * @return
   */
  inline static angle_t atan2(const double y, const double x) { return angle_t(std::atan2(y, x)); }

  /**
   * Returns true if this angle is non-zero
   * @return True if this angle is non-zero
   */
  inline operator bool() const { return value; }

  /**
   * Returns true if these angles are exactly equal
   */
  inline bool operator==(const angle_t& rhs) const { return value == rhs.value; }
  //inline bool operator!=(const angle_t& rhs) const { return value != rhs.value; }
  /**
   * Returns true if this is less than rhs
   */
  inline bool operator<(const angle_t& rhs) const { return value < rhs.value; }
  //inline bool operator>(const angle_t& rhs) const { return value > rhs.value; }
  //inline bool operator<=(const angle_t& rhs) const { return value <= rhs.value; }
  //inline bool operator>=(const angle_t& rhs) const { return value >= rhs.value; }

  inline std::ostream& operator<<(std::ostream& os)
  {
    os << value;
    return os;
  }
  inline std::istream& operator>>(std::istream& is)
  {
    is >> value;
    return is;
  }
};


inline angle_t operator"" _r(long double r)
{
  return angle_t::radians(r);
}

inline angle_t operator"" _d(long double d)
{
  return angle_t::degrees(d);
}


#endif
