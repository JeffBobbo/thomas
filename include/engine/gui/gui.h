#ifndef GUI_H_INCLUDE
#define GUI_H_INCLUDE

#include "window.h"

namespace engine
{
namespace gui
{
  engine::gui::Window* root();
  engine::gui::Element* focused();
  void init();
  void idle();
  void draw();
  void close();
}
}

#endif
