#include "Engine/Util/ActionTrigger.h"
#include "Engine/Event/ActionEvent.h"
#include "Engine/Exception.h"
#include "SDLWrapper.h"

namespace Engine {
namespace Util {

using Event::ActionEvent;

namespace {

struct TimerInit
{    
    void init()
    {
        if (!SDL::wasInit(SDL::INIT_TIMER) &&
            SDL::initSubSystem(SDL::INIT_TIMER) < 0)
            throw Exception("Couldn't initialize timer", SDL::getError());
    }
        
    ~TimerInit()
    {
         if (SDL::wasInit(SDL::INIT_TIMER))
              SDL::quitSubSystem(SDL::INIT_TIMER);
    }

} timerInit;

} // anonymous namespace

ActionTrigger::ActionTrigger()
    : repeats(true), delay(100), running(false)
{
    timerInit.init();
}

void ActionTrigger::start()
{
    id = SDL::addTimer(delay, callback, this);
    running = true;
}
    
void ActionTrigger::stop()
{
    SDL::removeTimer(id);
    running = false;
}
    
void ActionTrigger::addActionListener(ActionListener* l)
{
    mutex.lock();
    listener.push_back(l);
    mutex.unlock();
}

void ActionTrigger::removeActionListener(ActionListener* l)
{
    mutex.lock();
    listener.remove(l);
    mutex.unlock();
}

void ActionTrigger::trigger()
{
    if (!repeats)
        stop();
    mutex.lock();
    ActionEvent event(this);
    for (ListenerList::iterator i = listener.begin(); i != listener.end(); ++i)
        (*i)->actionEvent(event);
    mutex.unlock();
}
    
Uint32 ActionTrigger::callback(Uint32 interval, void* param)
{
    ((ActionTrigger*)param)->trigger();
    return ((ActionTrigger*)param)->delay;
}

} // namespace Util
} // namespace Engine
