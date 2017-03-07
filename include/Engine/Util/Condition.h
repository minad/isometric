#ifndef _Engine_Util_Condition_h
#define _Engine_Util_Condition_h

#include "Engine/Util/Mutex.h"
#include "SDLWrapper.h"

namespace Engine {
namespace Util {

class Condition
{
public:

    Condition()
    {
        cond = SDL::createCond();
    }

    ~Condition()
    {
        SDL::destroyCond(cond);
    }

    void wait(const Mutex& mutex)
    {
        SDL::condWait(cond, mutex.mutex);
    }

    bool waitTimeout(const Mutex& mutex, int timeout)
    {
        return (SDL::condWaitTimeout(cond, mutex.mutex, timeout) == 0);
    }

    void signal(bool all = false)
    {
        if (all)
            SDL::condBroadcast(cond);
        else
            SDL::condSignal(cond);    
    }

private:

    SDL::Cond* cond;
};

} // namespace Util
} // namespace Engine

#endif // _Engine_Util_Condition_h
