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

    std::vector<Element*>::iterator begin() { return std::begin(children); }
    std::vector<Element*>::iterator end() { return std::end(children); }
    const std::vector<Element*>& getChildren() const { return children; }

    inline virtual void setColour(const glm::vec4& c) final { colour = c; }
    inline virtual void setImage(GLint t) final { texture = t; }
  private:
    std::vector<Element*> children;
    glm::vec4 colour;
    GLint texture;
  };
}

#endif
