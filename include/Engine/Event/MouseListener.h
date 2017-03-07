#ifndef _Engine_Event_MouseListener_h
#define _Engine_Event_MouseListener_h

#include "Engine/Event/EventListener.h" 

namespace Engine {
namespace Event {

class MouseEvent;

struct MouseListener : public EventListener
{
    virtual void mouseEvent(const MouseEvent& event)
    {}

    virtual void mouseDownEvent(const MouseEvent& event)
    {
        mouseEvent(event);
    }

    virtual void mouseUpEvent(const MouseEvent& event)
    {
        mouseEvent(event);
    }
};

} // namespace Event
} // namespace Engine  

#endif // _Engine_Event_MouseListener_h

