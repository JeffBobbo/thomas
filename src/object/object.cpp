#include <object/object.h>

#include <thomas.h>

void thomas::object::Object::move()
{
  position += velocity * static_cast<float>(delta());
}

void thomas::object::Object::draw()
{
  if (visage)
    visage->draw();
}
