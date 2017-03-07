#ifndef _Engine_Event_Event_h
#define _Engine_Event_Event_h

namespace Engine {
namespace Event {

class EventSource;

struct Event
{
    EventSource* source;

    Event(EventSource* source)
        : source(source) {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_Event_h

