#ifndef _Engine_Event_ActionListener_h
#define _Engine_Event_ActionListener_h

#include "Engine/Event/EventListener.h" 

namespace Engine {
namespace Event {

class ActionEvent;

struct ActionListener : public EventListener
{
    virtual void actionEvent(const ActionEvent& event);
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_ActionListener_h

