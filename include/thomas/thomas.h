#ifndef ENGINE_H_INCLUDE
#define ENGINE_H_INCLUDE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#define GLT_MANUAL_VIEWPORT
//#include "external/gltext.h"

#include "event.h"


extern int screenWidth;
extern int screenHeight;
extern GLFWwindow* window;

namespace thomas
{
  void init(const int w, const int h, EventReceiver* const recv);
  void close();
  bool run();
  void beginFrame();
  void endFrame();
  void clear();
  void display();
}


#endif
