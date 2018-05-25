#ifndef INPUT_H_INCLUDE
#define INPUT_H_INCLUDE

#include <stdint.h>

#include "util/util.h"

namespace thomas
{
namespace input
{
namespace mouse
{
  struct Wheel
  {
    double x;
    double y;
  };
  struct MouseButton
  {
    int x;
    int y;
    int mod;
    bool pressed;
    millis_t last;
  };

  struct MouseState
  {
    MouseButton buttons[3];
    mouse::Wheel wheel;
    int x;
    int y;
    double velx;
    double vely;
    millis_t last;
  };

  bool left();
  bool middle();
  bool right();
  Wheel wheel();
  void velocity(double& x, double& y);
  millis_t idle();
  millis_t idle(const int b);

  void init();
}

namespace keyboard
{
  struct KeyState
  {
    bool pressed;
    int mod;
    millis_t last;
  };
  struct KeyboardState
  {
    KeyState keys[400]; // ASCII takes 0..255, leaves plenty of extra room for special keys
    millis_t last;
  };

  bool pressed(const int id);
  int modifiers(const int id);
  millis_t idle();
  millis_t idle(const int id);

  void init();
}

/*
namespace input
{
  void runEvents();
}
*/
}
}

#endif
