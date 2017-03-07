#ifndef _Engine_Event_WindowListener_h
#define _Engine_Event_WindowListener_h

#include "Engine/Event/EventListener.h" 

namespace Engine {
namespace Event {

class WindowEvent;

struct WindowListener : public EventListener
{
    virtual void windowActiveEvent(const WindowEvent& event)
    {}

    virtual void windowResizeEvent(const WindowEvent& event)
    {}

    virtual void windowCloseEvent(const WindowEvent& event)
    {}
};

} // namespace Event
} // namespace Engine  

#endif // _Engine_Event_WindowListener_h

