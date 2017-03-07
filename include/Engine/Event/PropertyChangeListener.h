#ifndef _Engine_Event_PropertyChangeListener_h
#define _Engine_Event_PropertyChangeListener_h

#include "Engine/Event/EventListener.h" 

namespace Engine {
namespace Event {

class PropertyChangeEvent;

struct PropertyChangeListener : public EventListener
{
    virtual void propertyChangeEvent(const PropertyChangeEvent& event)
    {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_PropertyChangeListener_h

