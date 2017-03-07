#ifndef _Engine_Audio_Channel_h
#define _Engine_Audio_Channel_h

#include "Engine/SmartPtr.h"
#include "Engine/Audio/Sound.h"
#include "SDLWrapper.h"

namespace Engine {
namespace Audio {

class Mixer;

class Channel
{
public:

    Channel();
    
    enum
    {
        MIN_VOLUME = 0,
        MAX_VOLUME = SDL::MIX_MAXVOLUME,
    };
    
    void play(Sound* sound);
    
    void playTimed(Sound* sound, int numLoops, int time);

    bool isFree() const
    {
        return free;
    }
    
    void setPaused(bool pause)
    {
        paused = pause;
    }

    bool isPaused() const
    {
        return paused;
    }
    
    void setRepeating(bool repeat)
    {
        repeating = repeat;
    }

    bool isRepeating() const
    {
        return repeating;
    }

    void setVolume(int v)
    {
        volume = v;
    }

    int getVolume() const
    {
        return volume;
    }

    void fadeOut(int time)
    {
        fadeTime = time;
        fading   = true;
    }

    Sound* getSound() const
    {
        return sound;
    }

private:

    friend class Mixer;

    SmartPtr<Sound> sound;
    Uint32 position;
    int    volume;
    int    numLoops, time;
    int    fadeTime;
    bool   repeating : 1;
    bool   paused    : 1;
    bool   free      : 1;
    bool   fading    : 1;
};

} // namespace Audio
} // namespace Engine

#endif // _Engine_Audio_Channel_h
