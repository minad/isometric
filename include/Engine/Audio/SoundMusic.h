#ifndef _Engine_Audio_SoundMusic_h
#define _Engine_Audio_SoundMusic_h

#include "Engine/Audio/Sound.h"
#include "SDLWrapper.h"
#include <string>

namespace Engine {
namespace Audio {

class SoundMusic : public Sound
{
public:

    SoundMusic(const std::string& file);
    ~SoundMusic();

    Uint32 decode(Uint8* samples, Uint32 start, Uint32 length);

private:
    
    Sound::Sample* sample;
    Uint32         position;
};

} // namespace Audio
} // namespace Engine

#endif // _Engine_Audio_SoundMusic_h
