#include <gui/label.h>

#include <iostream>

#include "../../external/gltext.h"

namespace engine
{
namespace gui
{
  const int Label::ALIGN_LEFT = GLT_LEFT;
  const int Label::ALIGN_CENTRE = GLT_CENTER;
  const int Label::ALIGN_RIGHT = GLT_RIGHT;
  const int Label::ALIGN_TOP = GLT_TOP;
  const int Label::ALIGN_MIDDLE = GLT_CENTER;
  const int Label::ALIGN_BOTTOM = GLT_BOTTOM;

  void Label::init()
  {
    gltInit();
  }
  void Label::terminate()
  {
    gltTerminate();
  }

  Label::Label()
  : size(12.0f / 17.0f)
  , hAlign(ALIGN_LEFT), vAlign(ALIGN_TOP)
  , colour(1.0f)
  {
    text = gltCreateText();
  }

  Label::~Label()
  {
    gltDeleteText(text);
  }

  void Label::draw() const
  {
    if (!isVisible())
      return;

    glm::ivec2 p, s;
    getRect(p, s);
    float x, y;
    switch (hAlign)
    {
      case ALIGN_LEFT:
        x = p.x;
      break;
      case ALIGN_CENTRE:
        x = p.x + s.x / 2.0f;
      break;
      case ALIGN_RIGHT:
        x = p.x + s.x;
      break;
    }
    switch (vAlign)
    {
      case ALIGN_TOP:
        y = p.y;
      break;
      case ALIGN_MIDDLE:
        y = p.y + s.y / 2.0f;
      break;
      case ALIGN_BOTTOM:
        y = p.y + s.y;
    }

    gltColor(colour.r, colour.g, colour.b, colour.a);
    gltDrawText2DAligned(text, x, y, 1.0f, hAlign, vAlign);
  }

  void Label::setText(const std::string& t)
  {
    gltSetText(text, t.c_str());
  }
}
}
