#include "Engine/Util/Thread.h"
#include <cassert>

namespace Engine {
namespace Util {

void Thread::start()
{
    assert(!thread);
    quitRequested = false;
    thread = SDL::createThread(callback, this);
}

int Thread::wait()
{
    if (!thread)
        return 0;
    int status;
    SDL::waitThread(thread, &status);
    thread = 0;
    return status;
}

int Thread::callback(void* data)
{
    int status = ((Thread*)data)->run();
    ((Thread*)data)->thread = 0;
    return status;
}

} // namespace Util
} // namespace Engine
