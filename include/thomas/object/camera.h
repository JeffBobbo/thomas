#ifndef CAMERA_H_INCLUDE
#define CAMERA_H_INCLUDE

#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../util/angle.h"
#include "../util/random.h"

namespace thomas
{
namespace object
{
class Camera
{
public:
  Camera()
  : targetObject(nullptr), targetPosition(0.0f)
  , sourceObject(nullptr), sourcePosition(0.0f)
  , upVector(0.0f, 1.0f, 0.0f)
  , near(0.1f), far(100000.0f)
  , fov(static_cast<float>(pi())/2.0f)
  {
  }
  virtual ~Camera() {}

  inline void setFOV(const float f)
  {
    fov = f;
  }
  inline void nearClip(const float f) { near = f; }
  inline void farClip(const float f) { far = f; }
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
    return glm::perspective(fov, width/height, near, far);
  }

  inline glm::vec3 lookingFrom() const
  {
    return sourceObject ? sourceObject->getPosition() : sourcePosition;
  }
  inline glm::vec3 lookingAt() const
  {
    return targetObject ? targetObject->getPosition() : targetPosition;
  }
  glm::mat4 getView() const;

  inline const glm::vec3& getPosition() const
  {
    return sourceObject ? sourceObject->getPosition() : sourcePosition;
  }

private:
  const Object* targetObject;
  glm::vec3 targetPosition;

  const Object* sourceObject;
  glm::vec3 sourcePosition;

  glm::vec3 upVector;

  float near, far;
  float fov;
};
}
}

#endif
