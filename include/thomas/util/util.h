#ifndef UTIL_H_INCLUDE
#define UTIL_H_INCLUDE

#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


template <typename T> inline T lerp(const T& a, const T& b, const double& p)
{
  return static_cast<T>((b - a) * p) + a;
}

template <typename T> inline T blerp(const T& x0, const T& y0, const T& x1, const T& y1, const double px, const double py)
{
  return lerp(lerp(x0, x1, px), lerp(y0, y1, px), py);
}

using millis_t = int64_t;
inline millis_t ticks() { return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1); }
millis_t start();
millis_t elapsed();
millis_t last();
millis_t delta();
double fps();

inline void updateTransform(const glm::vec3& inc, glm::mat4& rotation)
{
  //rotation about the local x axis
  glm::quat q = glm::angleAxis(inc.x, glm::vec3(rotation[0][0], rotation[0][1], rotation[0][2]));
  glm::mat4 matrixX = glm::mat4_cast(q) * rotation;

  //rotation about the local y axis
  q = glm::angleAxis(inc.y, glm::vec3(matrixX[1][0], matrixX[1][1], matrixX[1][2]));
  glm::mat4 matrixXY = glm::mat4_cast(q) * matrixX;

  //rotation about the local z axis
  q = glm::angleAxis(inc.z, glm::vec3(matrixXY[2][0], matrixXY[2][1], matrixXY[2][2]));
  rotation = glm::mat4_cast(q) * matrixXY;
}

#endif
