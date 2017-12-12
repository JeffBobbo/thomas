#ifndef GUI_ELEMENT_H_INCLUDE
#define GUI_ELEMENT_H_INCLUDE

#include <glm/glm.hpp>

#include "../receiver.h"
class Event;

namespace gui
{
  class Element : public EventReceiver
  {
  public:
    enum class Type
    {
      WINDOW
    };
    Element();
    virtual ~Element();

    virtual Type type() const = 0;

    virtual void draw() const = 0;

    glm::vec4 getPosition() const;

    inline void setParent(Element* e) { parent = e; }
    inline bool isVisible() const { return true; }

    void getRect(glm::ivec2& pos, glm::ivec2& size) const;

    virtual bool onEvent(const Event& e)
    {
      return parent ? parent->onEvent(e) : false;
    }

    glm::ivec4 position;
    glm::vec4 relative;
  protected:
    Element* parent;
  };
}

#endif
