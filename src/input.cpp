#include "input.h"

#include <cstring> // std::memset

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <thomas.h>
#include <gui/gui.h>
#include <gui/element.h>
#include <gui/window.h>

#include "internal.h"

using namespace thomas;
using namespace thomas::input;

mouse::MouseState m;
keyboard::KeyboardState k;

bool mouse::left()   { return m.buttons[0].pressed; }
bool mouse::middle() { return m.buttons[1].pressed; }
bool mouse::right()  { return m.buttons[2].pressed; }
mouse::Wheel mouse::wheel() { return m.wheel; }
millis_t mouse::idle() { return m.last; }
millis_t mouse::idle(const int b) { return m.buttons[b].last; }

void mouse::velocity(double& x, double& y)
{
  x = m.velx;
  y = m.vely;
}


glm::ivec2 lastpos = glm::ivec2(0);
void testEnterLeave(const glm::ivec2& npos, thomas::gui::Element* element)
{
  if (!element)
    return;
  if (element->type() == thomas::gui::Element::Type::WINDOW)
  {
    thomas::gui::Window* w = static_cast<thomas::gui::Window*>(element);
    for (thomas::gui::Element* child : *w)
      testEnterLeave(npos, child);
  }
  glm::ivec2 p, s;
  element->getRect(p, s);

  bool lastIn =
    lastpos.x >= p.x && lastpos.x <= p.x + s.x &&
    lastpos.y >= p.y && lastpos.y <= p.y + s.y;
  bool nowIn =
    npos.x >= p.x && npos.x <= p.x + s.x &&
    npos.y >= p.y && npos.y <= p.y + s.y;

  if (lastIn != nowIn)
  {
    thomas::Event e(thomas::Event::Type::GUI);
    e.gui.type = (nowIn) ? thomas::Event::GUIType::ELEMENT_ENTER : thomas::Event::GUIType::ELEMENT_LEAVE;
    e.gui.element = element;
    e.gui.caller = nullptr;
    element->onEvent(e);
  }
}

void motion(GLFWwindow* window, double x, double y)
{
  m.velx = (x - m.x) / delta();
  m.vely = (y - m.y) / delta();

  m.x = static_cast<int>(x);
  m.y = static_cast<int>(y);

  if (!receiver)
    return;

  thomas::Event e(thomas::Event::Type::MOUSE);
  e.mouse.type = thomas::Event::MouseType::MOVE;
  e.mouse.position = glm::ivec2(static_cast<int>(x), static_cast<int>(y));

  testEnterLeave(e.mouse.position, thomas::gui::root());
  lastpos = e.mouse.position;

  thomas::gui::onEvent(e);
}

void button(GLFWwindow* window, int button, int action, int mods)
{
  if (button < 3)
  {
    m.buttons[button].mod = mods;
    m.buttons[button].pressed = action == GLFW_PRESS || action == GLFW_REPEAT;
    m.buttons[button].last = elapsed();
  }

  if (!receiver)
    return;

  thomas::Event e(thomas::Event::Type::MOUSE);
  e.mouse.buttons = 0;
  switch (button)
  {
    case GLFW_MOUSE_BUTTON_LEFT:
      e.mouse.type = action == GLFW_PRESS ? thomas::Event::MouseType::LEFT_DOWN : thomas::Event::MouseType::LEFT_UP;
    break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      e.mouse.type = action == GLFW_PRESS ? thomas::Event::MouseType::MIDDLE_DOWN : thomas::Event::MouseType::MIDDLE_UP;
    break;
    case GLFW_MOUSE_BUTTON_RIGHT:
      e.mouse.type = action == GLFW_PRESS ? thomas::Event::MouseType::RIGHT_DOWN : thomas::Event::MouseType::RIGHT_UP;
    break;
  }
  e.mouse.buttons |= glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ? GLFW_MOUSE_BUTTON_LEFT : 0;
  e.mouse.buttons |= glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) ? GLFW_MOUSE_BUTTON_MIDDLE : 0;
  e.mouse.buttons |= glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) ? GLFW_MOUSE_BUTTON_RIGHT : 0;

  thomas::gui::onEvent(e);
}

void scroll(GLFWwindow* window, double x, double y)
{
  m.wheel.x = x;
  m.wheel.y = y;

  thomas::Event e(thomas::Event::Type::MOUSE);
  e.mouse.type = thomas::Event::MouseType::WHEEL;
  e.mouse.wheel = y;
  thomas::gui::onEvent(e);
}

void mouse::init()
{
  std::memset(m.buttons, 0, sizeof m.buttons);
  m.wheel.x = m.wheel.y = 0.0;
  m.x = m.y = 0;
  m.velx = m.vely = 0.0;
  m.last = 0;

  glfwSetMouseButtonCallback(window, button);
  glfwSetCursorPosCallback(window, motion);
  glfwSetScrollCallback(window, scroll);
}


/******************************************************************************/
/* KEYBOARD */
/******************************************************************************/
bool keyboard::pressed(const int id) { return k.keys[static_cast<int>(id)].pressed; }
int keyboard::modifiers(const int id) { return k.keys[static_cast<int>(id)].mod; }
millis_t keyboard::idle() { return k.last; }
millis_t keyboard::idle(const int id) { return k.keys[static_cast<int>(id)].last; }

void kb_action(GLFWwindow* window, int key, int scancode, int action, int mod)
{
  k.keys[key].pressed = action == GLFW_PRESS || action == GLFW_REPEAT;
  k.keys[key].mod = mod;
  k.keys[key].last = elapsed();
  if (!receiver)
    return;

  thomas::Event e(thomas::Event::Type::KEYBOARD);
  e.keyboard.character = key;
  e.keyboard.keycode = scancode;
  e.keyboard.pressed = action == GLFW_PRESS;
  e.keyboard.repeat = action == GLFW_REPEAT;
  e.keyboard.shift = mod & GLFW_MOD_SHIFT;
  e.keyboard.control = mod & GLFW_MOD_CONTROL;
  e.keyboard.alt = mod & GLFW_MOD_ALT;
  e.keyboard.super = mod & GLFW_MOD_SUPER;

  thomas::gui::onEvent(e);
}
void keyboard::init()
{
  std::memset(k.keys, 0, sizeof k.keys);
  k.last = 0;

  glfwSetKeyCallback(window, kb_action);
}
