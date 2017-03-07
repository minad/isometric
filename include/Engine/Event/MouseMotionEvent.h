#ifndef _Engine_Event_MouseMotionEvent_h
#define _Engine_Event_MouseMotionEvent_h

#include "Engine/Event/Event.h" 

namespace Engine {
namespace Event {

struct MouseMotionEvent : public Event
{
    enum
    {
        LEFT_MASK   = 0x1,
        MIDDLE_MASK = 0x2,
        RIGHT_MASK  = 0x4,
    };
    
    int buttonState;
    int x, y;
    int xrel, yrel;

    MouseMotionEvent(EventSource* source, int buttonState, int x, int y, int xrel, int yrel)
        : Event(source), buttonState(buttonState), x(x), y(y), xrel(xrel), yrel(yrel) {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_MouseMotionEvent_h

