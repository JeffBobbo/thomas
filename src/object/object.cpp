#include <object/object.h>

#include <thomas.h>

void Object::move()
{
  position += velocity * static_cast<float>(delta());
}

void Object::draw()
{
  if (visage)
    visage->draw();
}
