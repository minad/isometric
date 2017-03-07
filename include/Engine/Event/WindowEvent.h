#ifndef _Engine_Event_WindowEvent_h
#define _Engine_Event_WindowEvent_h

#include "Engine/Event/Event.h" 

namespace Engine {
namespace Event {

struct WindowEvent : public Event
{
    int  width, height;
    bool active;

    WindowEvent(EventSource* source, int width, int height, bool active)
        : Event(source), width(width), height(height), active(active) {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_WindowEvent_h

