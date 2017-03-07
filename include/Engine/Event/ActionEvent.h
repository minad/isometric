#ifndef _Engine_Event_ActionEvent_h
#define _Engine_Event_ActionEvent_h

#include "Engine/Event/Event.h" 

namespace Engine {
namespace Event {

struct ActionEvent : public Event
{
    ActionEvent(EventSource* source)
        : Event(source) {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_ActionEvent_h

