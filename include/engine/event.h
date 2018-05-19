#ifndef EVENT_H_INCLUDE
#define EVENT_H_INCLUDE

#include <stdint.h>

#include <glm/glm.hpp>

#include "gui/element.h"

class Event
{
public:
  enum class Type
  {
    GUI,
    KEYBOARD,
    MOUSE
  };

  enum class MouseType
  {
    LEFT_DOWN,
    MIDDLE_DOWN,
    RIGHT_DOWN,
    LEFT_UP,
    MIDDLE_UP,
    RIGHT_UP,
    MOVE,
    WHEEL
  };

  static const int8_t MOUSE_LEFT_MASK = 0x01;
  static const int8_t MOUSE_MIDDLE_MASK = 0x02;
  static const int8_t MOUSE_RIGHT_MASK = 0x04;

  enum class GUIType
  {
    FOCUS_LOST,
    FOCUS_GAIN,
    ELEMENT_ENTER,
    ELEMENT_LEAVE
  };

  struct GUIEvent
  {
    engine::gui::Element* caller;
    engine::gui::Element* element;
    Event::GUIType type;
  };

  struct MouseInput
  {
    glm::ivec2 position;
    float wheel;
    bool shift : 1;
    bool control : 1;
    uint32_t buttons;
    MouseType type;
    inline bool left() const { return buttons & MOUSE_LEFT_MASK; }
    inline bool middle() const { return buttons & MOUSE_MIDDLE_MASK; }
    inline bool right() const { return buttons & MOUSE_RIGHT_MASK; }
  };

  struct KeyInput
  {
    wchar_t character;
    int keycode;
    bool pressed : 1;
    bool repeat : 1;
    bool shift : 1;
    bool control : 1;
    bool alt : 1;
    bool super : 1;
  };

  Event(Type t) : type(t) {}

  const Type type;
  union
  {
    GUIEvent gui;
    MouseInput mouse;
    KeyInput keyboard;
  };
};

#endif
