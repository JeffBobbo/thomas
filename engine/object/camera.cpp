#include "camera.h"

glm::vec3 Camera::getShake()
{
  if (shakeFrom == shakeTo)
    return glm::vec3(0.0f);

  if (elapsed() - shakeStart > shakeTime)
  {
    shakeStart = elapsed();
    shakeFrom = shakeTo;
    shakeTo = glm::vec3(random(-shakiness, shakiness), random(-shakiness, shakiness), random(-shakiness, shakiness));
  }

  return glm::mix(shakeFrom, shakeTo, (elapsed()-shakeStart) / static_cast<float>(shakeTime));
}

glm::mat4 Camera::getView()
{
  glm::vec3 f = lookingFrom(), a = lookingAt();
  if (f == a)
    return glm::lookAt(
      f,
      a + glm::vec3(0.0f, 10.0f, 0.0),
      upVector
    );

  return glm::lookAt(
    f,// + getShake(),
    a,
    upVector
  );
}

void Camera::setShakiness(const float sf)
{
  glm::clamp(sf, 0.0f, 1.0f);
  shakiness = sf;
  shakeTime = shakeDuration(sf);
  shakeFrom = getShake();
  if (sf <= 0.0f)
    shakeTo = glm::vec3(0.0f);
  else
    shakeTo = glm::vec3(random(-sf, sf), random(-sf, sf), random(-sf, sf));
}
