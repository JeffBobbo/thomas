#ifndef ENGINE_H_INCLUDE
#define ENGINE_H_INCLUDE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/event.h"

extern int screenWidth;
extern int screenHeight;
extern GLFWwindow* window;

namespace engine
{
  void init(const int w, const int h, EventReceiver* const recv);
  void close();
  bool run();
  void beginFrame();
  void endFrame();
}


#endif
