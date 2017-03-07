#include "Engine/Audio/Mixer.h"
#include "Engine/Audio/Sound.h"
#include "Engine/Exception.h"

namespace Engine {
namespace Audio {

SmartPtr<Mixer> Mixer::instance;

Mixer::Mixer()
{
    SDL::AudioSpec desired;
    
    desired.freq = 44100;         
    desired.format = AUDIO_S16;
    desired.samples = 4096;   
    desired.channels = 2;    
    desired.callback = callback;
    desired.userdata = this;	    

    if (SDL::openAudio(&desired, &spec) < 0)
        throw Exception("Unable to open audio devic", SDL::getError());

    setNumChannels(16);
    pauseAll(false);
}

Mixer::~Mixer()
{
    pauseAll(true);
}

void Mixer::setNumChannels(int n)
{
    SDL::lockAudio();
    channels.resize(n);
    SDL::unlockAudio();
}

Channel* Mixer::getFreeChannel()
{
    for (Uint32 i = 0; i < channels.size(); ++i) 
    {
        if (channels[i].free)
	     return &(channels[i]);
    }
    assert(!"No free channel available");
    return 0;
}

void Mixer::mixChannels(Uint8* audio, Uint32 length)
{
    timer.nextFrame();
    Uint32 frameTime = timer.getFrameTime();

    memset(audio, 0, length);
    for (ChannelVector::iterator i = channels.begin(); i != channels.end(); ++i)
    {
        if (i->free || i->paused)
	    continue;
	
	//Uint32 samplesLen = i->sound->decode(samples, i->position, length);
	Uint32 samplesLen = i->sound->getLength() - i->position;
	if (samplesLen > length)
	    samplesLen = length;
	SDL::mixAudio(audio, const_cast<Uint8*>(i->sound->getSamples()) + i->position, samplesLen, i->volume);

        i->position += samplesLen;

        if (i->time > 0)
	    i->time -= frameTime;

        if (samplesLen < length)
	{
            if (i->repeating || --(i->numLoops) > 0 || i->time > 0)
	        i->position = 0;
	    else
	    {
	        i->free = true;
	        i->sound = 0;
	    }
	}

        if (i->fading)
        {
            i->volume -= frameTime * i->volume / i->fadeTime;
            i->fadeTime -= frameTime;
            if (i->fadeTime <= 0)
            {
                i->free = true;
                i->sound = 0;
                i->fading = false;
	    }
        }
    }
}

void Mixer::callback(void* userData, Uint8* audio, int length)
{
    ((Mixer*)userData)->mixChannels(audio, length);
}

Mixer* Mixer::getInstance()
{
    if (!instance)
        instance = new Mixer();
    return instance;
}

} // namespace Audio
} // namespace Engine
