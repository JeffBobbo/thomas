#ifndef PARTICLE_H_INCLUDE
#define PARTICLE_H_INCLUDE

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "visage.h"
#include "../util/colour.h"
#include "../util/interval.h"
#include "../util/util.h"

namespace thomas
{
namespace visage
{
struct Particle
{
  Particle() : age(0) {};

  glm::vec3 pos;
  glm::vec3 vel;
  glm::vec4 col;
  float size;

  millis_t lifespan;
  millis_t age;
};

class ParticleSystem : public Visage
{
public:
  ParticleSystem();
  virtual ~ParticleSystem();

  virtual inline Type type() const { return Type::PARTICLE; }

  virtual void draw();

  inline bool empty() const { return particles == last; }
  inline bool full() const { return end == last; }

private:
  Particle* particles;
  Particle* last;
  Particle* end;
  const size_t max;

  GLuint quad_vao;
  GLuint quad_vbo;
  GLuint quad_ebo;
  GLuint texture;

  // stuff about the particles emitted
  thomas::util::interval_t interval; // the rate

  // how long they live, in ms
  millis_t lifeMin;
  millis_t lifeMax;

  float sizeStart;
  float sizeEnd;
  float speedStart;
  float speedEnd;

  // start and end colour
  ARGB c0, c1;

  void add(int n);
  void erase(Particle* p);
  void update();
public:
};
}
}

#endif
