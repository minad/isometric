#ifndef _Engine_Event_MouseEvent_h
#define _Engine_Event_MouseEvent_h

#include "Engine/Event/Event.h"

namespace Engine {
namespace Event {

struct MouseEvent : public Event
{
    enum Button
    {
        LEFT,
        MIDDLE,
        RIGHT,
        WHEELUP,
        WHEELDOWN,
    };
    
    Button button;
    int    x, y;
    bool   pressed;

    MouseEvent(EventSource* source, Button button, int x, int y, bool pressed)
        : Event(source), button(button), x(x), y(y), pressed(pressed) {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_MouseEvent_h

