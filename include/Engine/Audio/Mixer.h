#ifndef _Engine_Audio_Mixer_h
#define _Engine_Audio_Mixer_h

#include "Engine/Audio/Channel.h"
#include "Engine/Base.h"
#include "Engine/SmartPtr.h"
#include "Engine/Util/FrameTimer.h"
#include "SDLWrapper.h"
#include <vector>

namespace Engine {
namespace Audio {

class Mixer : public Base
{
public:

    enum
    {
        MIN_VOLUME = 0,
	MAX_VOLUME = SDL::MIX_MAXVOLUME,
    };

    void setNumChannels(int n);
    
    int getNumChannels() const
    {
        return channels.size();
    }

    Channel* getChannel(int i)
    {
        return &(channels.at(i));
    }
    
    Channel* getFreeChannel();
    
    void pauseAll(bool pause)
    {
        SDL::pauseAudio(pause ? 1 : 0);
    }

    const SDL::AudioSpec& getSpec() const
    {
        return spec;
    }

    static Mixer* getInstance();

private:

    static void callback(void* userData, Uint8* audio, int length);

    Mixer();
    ~Mixer();

    void mixChannels(Uint8* data, Uint32 length);

    typedef std::vector<Channel> ChannelVector;
    ChannelVector channels;

    Util::FrameTimer timer;

    SDL::AudioSpec spec;

    static SmartPtr<Mixer> instance;
};

} // namespace Audio
} // namespace Engine

#endif // _Engine_Audio_Mixer_h
