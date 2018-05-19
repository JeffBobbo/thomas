#ifndef ANIMATRIX_H_INCLUDE
#define ANIMATRIX_H_INCLUDE

#include "../util/angle.h"
#include "../util/matrix.h"
#include "../util/util.h"

class Animatrix
{
public:
  Animatrix() : scale(1.0f), angle(0.0f) {}

  void apply() const
  {
    //translate
    Matrix::rotate(angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
    Matrix::rotate(angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
    Matrix::rotate(angle.z, glm::vec3(0.0f, 0.0f, 1.0f));
    Matrix::scale(scale);
  }

  glm::vec3 scale;
  glm::vec3 angle; // a really bad rotation in xyz, rather than a quat
private:
};

#endif
