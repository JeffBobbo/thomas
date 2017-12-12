#ifndef RECEIVER_H_INCLUDE
#define RECEIVER_H_INCLUDE

class Event;

class EventReceiver
{
public:
  virtual ~EventReceiver() {}

  virtual bool onEvent(const Event& event) = 0;
};

#endif
