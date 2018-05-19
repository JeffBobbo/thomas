#ifndef GUI_LABEL_H_INCLUDE
#define GUI_LABEL_H_INCLUDE

#include "element.h"

#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>

struct GLTtext;

namespace engine
{
namespace gui
{
  class Label : public Element
  {
  public:
    static const int ALIGN_LEFT;
    static const int ALIGN_CENTRE;
    static const int ALIGN_RIGHT;
    static const int ALIGN_TOP;
    static const int ALIGN_MIDDLE;
    static const int ALIGN_BOTTOM;

    // functions to handle glt's context creation and destruction
    static void init();
    static void terminate();

    // actual class stuff
    Label();
    virtual ~Label();

    inline virtual Type type() const override { return Element::Type::LABEL; }

    virtual void idle() final {};
    virtual void draw() const final;

    void setText(const std::string& t);
    inline void setSize(const float& s) { size = s / 17.0f; }
    inline void setHAlignment(const int h) { hAlign = h; }
    inline void setVAlignment(const int v) { vAlign = v; }
    inline void setColour(const glm::vec4& c) { colour = c; }
  private:
    GLTtext* text;
    float size;
    // alignment
    int hAlign;
    int vAlign;
    glm::vec4 colour;
  };
}
}

#endif
