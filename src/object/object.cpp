#include <object/object.h>

#include <engine.h>

void Object::move()
{
  position += velocity * static_cast<float>(delta());
}

void Object::draw()
{
  if (visage)
    visage->draw();
}
