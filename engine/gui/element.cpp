#include "element.h"

#include "../../engine.h"

namespace gui
{
  Element::Element()
  // : pos(glm::vec2(0.0f, 0.0f)), size(glm::vec2(0.0f, 0.0f))
  : position(glm::ivec4(0, 0, 1, 1)), relative(glm::vec4(0.0f, 0.8f, 1.0f, 1.0f))
  , parent(nullptr)
  {
  }
  Element::~Element()
  {
  }

/*
  glm::vec4 Element::getPosition() const
  {
    glm::vec4 p;
    if (parent)
    {
      glm::vec4 q = parent->getPosition();
      p.x = q + relative.x * (q.z-q.x) * position.x;
      p.y = q + relative.y * (q.w-q.y) * position.y;
      p.w = q + relative.w * (q.z-q.x) * position.z;
      p.z = q + relative.z * (q.w-q.y) * position.w;
    }
    else
    {
      p.x = relative.x * screenWidth + position.x;
      p.y = relative.y * screenHeight + position.y;
      p.z = relative.z * screenWidth + position.z;
      p.w = relative.w * screenHeight + position.w;
    }
    return p;
  }
  */

  void Element::getRect(glm::ivec2& pos, glm::ivec2& size) const
  {
    glm::ivec4 r;
    if (parent)
    {
      glm::ivec2 p, s;
      parent->getRect(p, s);
      r.x = static_cast<int>(p.x + relative.x * (s.x) + position.x);
      r.y = static_cast<int>(p.y + relative.y * (s.y) + position.y);
      r.z = static_cast<int>(p.x + relative.z * (s.x) + position.z);
      r.w = static_cast<int>(p.y + relative.w * (s.y) + position.w);
    }
    else
    {
      r.x = static_cast<int>(relative.x * screenWidth + position.x);
      r.y = static_cast<int>(relative.y * screenHeight + position.y);
      r.z = static_cast<int>(relative.z * screenWidth + position.z);
      r.w = static_cast<int>(relative.w * screenHeight + position.w);
    }

    pos.x = r.x;
    pos.y = r.y;
    size.x = r.z - r.x;
    size.y = r.w - r.y;
  }
}
