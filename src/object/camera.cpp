#include <object/camera.h>

glm::mat4 thomas::object::Camera::getView() const
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
