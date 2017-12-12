#ifndef OBJECT_H_INCLUDE
#define OBJECT_H_INCLUDE

#include <glm/glm.hpp>

#include "../util/util.h"
#include "../visage/visage.h"

class Object
{
public:
  enum class Type
  {
  };

  Object()
   : position(0.0f), velocity(0.0f), rotation(0.0f)
   , size(1.0f)
   , visage(nullptr)
   , born(elapsed()) {};
  virtual ~Object() {};

  inline millis_t birth() const { return born; }
  inline millis_t age() const { return elapsed() - born; }

  inline void setVisage(Visage* const v) { visage = v; }
  //virtual inline Type type() const =0;

  virtual void idle() {}
  virtual void move();
  virtual void draw();

  virtual inline float distance(const Object* const obj) const final
  {
    return glm::distance(position, obj->position);
  }

  inline const glm::vec3& getPosition() const { return position; }
  inline const glm::vec3& getVelocity() const { return velocity; }
  inline const glm::vec3& getRotation() const { return rotation; }

public:
  glm::vec3 position;
  glm::vec3 velocity;
  glm::vec3 rotation;
  float size; // uniform scaling of the object
  Visage* visage;
protected:
private:

  const millis_t born;

};

#endif
