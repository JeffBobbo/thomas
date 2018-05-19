#ifndef VISAGE_H_INCLUDE
#define VISAGE_H_INCLUDE

#include <vector>

#include <GL/glew.h>

#include "animatrix.h"

namespace thomas
{
namespace visage
{
class Visage
{
public:
  enum class Type
  {
    COMPLEX,
    PARTICLE,
    MESH,
    SKYBOX
  };

  Visage() : blend(false), cull(true) {}
  virtual ~Visage()
  {
    for (Animatrix* a : animatrices)
      delete a;
  }

  virtual inline Type type() const = 0;

  virtual void draw()
  {
    if (blend)
      glEnable(GL_BLEND);
    else
      glDisable(GL_BLEND);
    if (cull)
      glEnable(GL_CULL_FACE);
    else
      glDisable(GL_CULL_FACE);
    for (const Animatrix* const ani : animatrices)
      ani->apply();
    Matrix::apply();
  };
  virtual void addAnimatrix(Animatrix* const a) { animatrices.push_back(a); }

  inline void doesBlend(const bool b) { blend = b; }
  inline void doesCull(const bool c) { cull = c; }

protected:
  std::vector<Animatrix* > animatrices;
  bool blend;
  bool cull;
};
}
}

#endif
