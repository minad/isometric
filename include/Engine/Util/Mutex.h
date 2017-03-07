#ifndef _Engine_Util_Mutex_h
#define _Engine_Util_Mutex_h

#include "SDLWrapper.h"

namespace Engine {
namespace Util {

class Condition;

class Mutex
{
public:

    Mutex()
    {
        mutex = SDL::createMutex();
    }

    ~Mutex()
    {
        SDL::destroyMutex(mutex);
    }

    void lock()
    {
        SDL::lockMutex(mutex);
    }

    void unlock()
    {
        SDL::unlockMutex(mutex);
    }

private:

    SDL::Mutex* mutex;
    friend class Condition;
};

} // namespace Util
} // namespace Engine

#endif // _Engine_Util_Mutex_h
