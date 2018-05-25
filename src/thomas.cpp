#include <thomas.h>

#include <event.h>
#include <util/util.h>

#include "internal.h"

int screenWidth;
int screenHeight;
GLFWwindow* window = nullptr;
thomas::EventReceiver* receiver = nullptr;

void resize(GLFWwindow* window, int width, int height)
{
  (void)window;
  screenWidth = width;
  screenHeight = height;

  glViewport(0, 0, width, height); // reset OpenGL's viewport
  //gltViewport(width, height); // reset gltext's viewport
}

void thomas::init(const int w, const int h, EventReceiver* const recv)
{
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  screenWidth = w;
  screenHeight = h;
  window = glfwCreateWindow(w, h, "", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, resize);

  glewExperimental = GL_TRUE;
  glewInit();

  glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
  glEnable(GL_DEPTH_TEST);

  receiver = recv;
  initTicks();

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glEnable(GL_MULTISAMPLE);
}

void thomas::close()
{
  //gltTerminate();
  glfwTerminate();
}

bool thomas::run()
{
  return !glfwWindowShouldClose(window);
}

void thomas::beginFrame()
{
  updateTicks();
}

void thomas::endFrame()
{
  glfwPollEvents();
}

void thomas::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void thomas::display()
{
  glfwSwapBuffers(window);
}
