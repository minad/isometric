#ifndef _Engine_Util_ActionTrigger_h
#define _Engine_Util_ActionTrigger_h

#include "Engine/Event/ActionListener.h"
#include "Engine/Event/EventSource.h"
#include "Engine/Util/Mutex.h"
#include "SDLWrapper.h"
#include <list>

namespace Engine {
namespace Util {

using Event::ActionListener;
using Event::EventSource;

class ActionTrigger : public EventSource
{
public:

    ActionTrigger();

    void setDelay(int d)
    {
        delay = d;
    }
    
    int getDelay()
    {
        return delay;
    }
    
    bool isRepeats() const
    {
        return repeats;
    }
    
    void setRepeats(bool r)
    {
        repeats = r;
    }
    
    bool isRunning() const
    {
        return running;
    }
    
    void start();
    
    void stop();
    
    void addActionListener(ActionListener* l);
    
    void removeActionListener(ActionListener* l);
    
private:

    void trigger();

    static Uint32 callback(Uint32 interval, void* param);

    SDL::TimerID id;
    bool repeats;
    int  delay;
    bool running;
    typedef std::list<ActionListener*> ListenerList;
    ListenerList listener;
    Mutex mutex;
};

} // namespace Util
} // namespace Engine

#endif // _Engine_Util_ActionTrigger_h
