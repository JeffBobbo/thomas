#ifndef GUI_H_INCLUDE
#define GUI_H_INCLUDE

#include "window.h"

namespace gui
{
  gui::Window* root();
  gui::Element* focused();
  void init();
  void idle();
  void draw();
  void close();
}

#endif
