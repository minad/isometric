#include "Engine/Audio/Channel.h"
#include "Engine/Exception.h"

namespace Engine {
namespace Audio {

Channel::Channel()
    : position(0), volume(MAX_VOLUME), numLoops(-1), time(-1),
      fadeTime(-1), repeating(false), paused(false), free(true), fading(false)
{
}

void Channel::play(Sound* s)
{
    SDL::lockAudio();
    sound    = s;
    free     = false;
    position = 0;
    numLoops = 0;
    time     = 0;
    SDL::unlockAudio();
}

void Channel::playTimed(Sound* s, int n, int t)
{
    SDL::lockAudio();
    sound    = s;
    numLoops = n;
    time     = t;
    free     = false;
    position = 0;
    SDL::unlockAudio();
}

} // namespace Audio
} // namespace Engine
