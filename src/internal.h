#ifndef UTIL_INTERNAL_H_INCLUDE
#define UTIL_INTERNAL_H_INCLUDE

#include "event.h"

void initTicks();
void updateTicks();

extern thomas::EventReceiver* receiver;

namespace thomas
{
namespace gui
{
  void onEvent(const Event& e);
}
}

#endif
