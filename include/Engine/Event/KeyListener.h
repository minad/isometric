#ifndef _Engine_Event_KeyListener_h
#define _Engine_Event_KeyListener_h

#include "Engine/Event/EventListener.h"

namespace Engine {
namespace Event {

class KeyEvent;

struct KeyListener : public EventListener
{
    virtual void keyEvent(const KeyEvent& event)
    {}

    virtual void keyDownEvent(const KeyEvent& event)
    {
        keyEvent(event);
    }

    virtual void keyUpEvent(const KeyEvent& event)
    {
        keyEvent(event);
    }
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_KeyListener_h

