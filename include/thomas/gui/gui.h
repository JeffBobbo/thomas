#ifndef GUI_H_INCLUDE
#define GUI_H_INCLUDE

#include "window.h"

namespace thomas
{
namespace gui
{
  thomas::gui::Window* root();
  thomas::gui::Element* focused();
  void init();
  void idle();
  void draw();
  void close();
}
}

#endif
