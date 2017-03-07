#ifndef _Engine_Util_FrameTimer_h
#define _Engine_Util_FrameTimer_h

#include "SDLWrapper.h"

namespace Engine {
namespace Util {

class FrameTimer
{
public:

    FrameTimer()
        : frameRate(0), frames(0), oldTime(0), startTime(0)
    {
    }

    Uint32 getTime() const
    {
        return SDL::getTicks();
    }

    Uint32 getFrameTime() const
    {
        return frameTime;
    }

    float getFrameRate() const
    {
        return frameRate;
    }

    void nextFrame();

    void reset()
    {
        frameRate = 0;
	frames = frameTime = oldTime = startTime = 0; 
    }

private:

    float  frameRate;
    int    frames; // Frames seit startTime
    Uint32 frameTime, oldTime,
           startTime; // Startzeit für Messung von frameRate
};

} // namespace Util
} // namespace Engine

#endif // _Engine_Util_FrameTimer_h
