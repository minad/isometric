#ifndef _Engine_Event_PropertyChangeEvent_h
#define _Engine_Event_PropertyChangeEvent_h

#include "Engine/Event/Event.h"
#include <string>

namespace Engine {
namespace Event {

struct PropertyChangeEvent : public Event
{
    std::string property;

    PropertyChangeEvent(EventSource* source, const std::string& property)
        : Event(source), property(property) {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_PropertyChangeEvent_h

