#ifndef GUI_WINDOW_H_INCLUDE
#define GUI_WINDOW_H_INCLUDE

#include "element.h"

#include <vector>

#include <GL/glew.h>

namespace gui
{
  class Window : public Element
  {
  public:
    Window();
    virtual ~Window();

    inline virtual Type type() const override { return Element::Type::WINDOW; }

    virtual void draw() const final;

    virtual bool onEvent(const Event& e)
    {
      for (auto& it : children)
      {
        if (it->onEvent(e))
          return true;
      }
      return false;
    }

    virtual void add(Element* child) final
    {
      children.push_back(child);
      child->setParent(this);
    }
    virtual void removeChildren() final
    {
      for (auto& it : children)
        delete it;
      children.clear();
    }

    virtual std::vector<Element*>::iterator begin() final { return std::begin(children); }
    virtual std::vector<Element*>::iterator end() final { return std::end(children); }
    virtual const std::vector<Element*>& getChildren() const final { return children; }

    inline virtual void setColour(const glm::vec4& c) final { colour = c; }
    inline virtual void setImage(GLint t) final { texture = t; }
  protected:
    std::vector<Element*> children;
    glm::vec4 colour;
    GLint texture;
  };
}

#endif
