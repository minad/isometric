#include "Engine/Util/FrameTimer.h"

namespace Engine {
namespace Util {

void FrameTimer::nextFrame()
{
    Uint32 newTime = getTime();
    
    if (oldTime == 0 && startTime == 0)
    {
        oldTime = startTime = newTime;
	return;
    }
   
    ++frames;
   
    Uint32 diff = newTime - startTime;
    if (diff > 200)
    {
        frameRate = frames / (diff * .001f);
	frames = 0;
	startTime = newTime;
    }
    
    frameTime = newTime - oldTime;
    oldTime = newTime;
}

} // namespace Util
} // namespace Engine

