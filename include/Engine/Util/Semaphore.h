#ifndef _Engine_Util_Semaphore_h
#define _Engine_Util_Semaphore_h

#include "SDLWrapper.h"

namespace Engine {
namespace Util {

class Semaphore
{
public:

    Semaphore(int nr)
    {
        sem = SDL::createSemaphore(nr);
    }

    ~Semaphore()
    {
        SDL::destroySemaphore(sem);
    }

    void lock()
    {
        SDL::semWait(sem);
    }
    
    bool lockTry()
    {
        return (SDL::semTryWait(sem) == 0);
    }
    
    bool lockTimeout(int timeout)
    {
        return (SDL::semWaitTimeout(sem, timeout) == 0);
    }
    
    void unlock()
    {
        SDL::semPost(sem);
    }

    int getValue() const
    {
        return SDL::semValue(sem);
    }

private:

    SDL::Sem* sem;
};

} // namespace Util
} // namespace Engine

#endif // _Engine_Util_Semaphore_h
