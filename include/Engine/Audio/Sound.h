#ifndef _Engine_Audio_Sound_h
#define _Engine_Audio_Sound_h

#include "Engine/Base.h"
#include "SDLWrapper.h"
#include <string>

namespace Engine {
namespace Audio {

class Sound : public Base
{
public:
	
    Sound(const std::string& file);
    ~Sound();

    const Uint8* getSamples() const
    {
        return samples;
    }
    
    Uint32 getLength() const
    {
        return length;
    }

private:

    Uint8* samples;
    Uint32 length;
};

} // namespace Audio
} // namespace Engine

#endif // _Engine_Audio_Sound_h
