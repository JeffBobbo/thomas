#ifndef CAMERA_H_INCLUDE
#define CAMERA_H_INCLUDE

#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../util/angle.h"
#include "../util/random.h"

class Camera
{
public:
  Camera()
  : targetObject(nullptr), targetPosition(0.0f)
  , sourceObject(nullptr), sourcePosition(0.0f)
  , upVector(0.0f, 1.0f, 0.0f)
  , fov(90.0_d)
  , shakiness(0.0f), shakeFrom(0.0f), shakeTo(0.0f), shakeStart(0), shakeTime(0)
  {
  }
  virtual ~Camera() {}

  inline void setFOV(const angle_t f)
  {
    fov = f;
  }
  inline void target(const Object* o)
  {
    targetObject = o;
  }
  inline void target(const glm::vec3& p)
  {
    targetObject = nullptr;
    targetPosition = p;
  }
  inline void source(const Object* o)
  {
    sourceObject = o;
  }
  inline void source(const glm::vec3& p)
  {
    sourceObject = nullptr;
    sourcePosition = p;
  }
  inline void up(const glm::vec3& p)
  {
    upVector = p;
  }
  inline glm::mat4 getProjection(const float width, const float height) const
  {
    return glm::perspective(static_cast<float>(fov.radians()), width/height, 0.1f, 1000000.0f);
  }

  glm::vec3 getShake();

  inline glm::vec3 lookingFrom()
  {
    return sourceObject ? sourceObject->getPosition() : sourcePosition;
  }
  inline glm::vec3 lookingAt()
  {
    return targetObject ? targetObject->getPosition() : targetPosition;
  }
  glm::mat4 getView();

  inline const glm::vec3& getPosition() const
  {
    return sourceObject ? sourceObject->getPosition() : sourcePosition;
  }

private:
  inline millis_t shakeDuration(const float sf)
  {
    return static_cast<millis_t>(500.0f - (sf * 250.0f));
  }
public:
  void setShakiness(const float sf);

private:
  const Object* targetObject;
  glm::vec3 targetPosition;

  const Object* sourceObject;
  glm::vec3 sourcePosition;

  glm::vec3 upVector;

  angle_t fov;

  float shakiness;
  glm::vec3 shakeFrom;
  glm::vec3 shakeTo;
  millis_t shakeStart;
  millis_t shakeTime;
};

extern Camera camera;

#endif
