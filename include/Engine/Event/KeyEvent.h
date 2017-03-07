#ifndef _Engine_Event_KeyEvent_h
#define _Engine_Event_KeyEvent_h

#include "Engine/Event/Event.h"
#include "SDLWrapper.h"

namespace Engine {
namespace Event {

struct KeyEvent : public Event
{
    SDL::Key key;
    SDL::Mod mod;
    Uint16   unicode;
    bool     pressed;

    KeyEvent(EventSource* source, SDL::Key key, SDL::Mod mod, Uint16 unicode, bool pressed)
        : Event(source), key(key), mod(mod), unicode(unicode), pressed(pressed) {}
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_KeyEvent_h

