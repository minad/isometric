#ifndef _Engine_Util_Thread_h
#define _Engine_Util_Thread_h

#include "SDLWrapper.h"

namespace Engine {
namespace Util {

class Thread
{
public:

    Thread() : quitRequested(false), thread(0) {}
    virtual ~Thread() { }
    
    void start();
    int wait();

    void requestQuit()
    {
        quitRequested = true;
    }

    bool isQuitRequested() const
    {
        return quitRequested;
    }

protected:

    virtual int run() = 0;

private:

    static int callback(void* data);

    bool quitRequested;
    SDL::Thread* thread;
};

} // namespace Util
} // namespace Engine

#endif // _Engine_Util_Thread_h
