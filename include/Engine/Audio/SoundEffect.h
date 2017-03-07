#ifndef _Engine_Audio_SoundEffect_h
#define _Engine_Audio_SoundEffect_h

#include "Engine/Audio/Sound.h"
#include "SDLWrapper.h"
#include <string>

namespace Engine {
namespace Audio {

class SoundEffect : public Sound
{
public:

    SoundEffect(const std::string& file);
    ~SoundEffect();

    Uint32 decode(Uint8* samples, Uint32 start, Uint32 length);

private:

    Uint8* samples;
    Uint32 length;
};

} // namespace Audio
} // namespace Engine

#endif // _Engine_Audio_SoundEffect_h
