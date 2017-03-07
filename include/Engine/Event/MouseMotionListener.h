#ifndef _Engine_Event_MouseMotionListener_h
#define _Engine_Event_MouseMotionListener_h

#include "Engine/Event/EventListener.h" 

namespace Engine {
namespace Event {

class MouseMotionEvent;

struct MouseMotionListener : public EventListener
{
    virtual void mouseMotionEvent(const MouseMotionEvent& event)
    {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_MouseMotionListener_h

