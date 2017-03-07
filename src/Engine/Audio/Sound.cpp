#include "Engine/Audio/Sound.h"
#include "Engine/Audio/Mixer.h"
#include "Engine/Exception.h"
#include <cstring>

namespace Engine {
namespace Audio {

Sound::Sound(const std::string& name)
{
    SDL::AudioSpec spec;
    if (!SDL::loadWAV(name.c_str(), &spec, &samples, &length))
        throw Exception("Unable to load sound", SDL::getError());

    SDL::AudioSpec destSpec = Mixer::getInstance()->getSpec();

    SDL::AudioCVT cvt;
    if (SDL::buildAudioCVT(&cvt, spec.format, spec.channels, spec.freq,
                           destSpec.format, destSpec.channels, destSpec.freq) < 0)
        throw Exception("Unable to convert sound", SDL::getError());

    cvt.len = length;
    cvt.buf = new Uint8[cvt.len * cvt.len_mult];
    memcpy(cvt.buf, samples, length);

    if (SDL::convertAudio(&cvt) < 0)
    {
        delete cvt.buf;
        SDL::freeWAV(samples);        
        throw Exception("Audio conversion error", SDL::getError());
    }

    SDL::freeWAV(samples);

    samples = cvt.buf;
    length = cvt.len * cvt.len_mult;
/*
    SDL::AudioSpec destSpec = Mixer::getInstance()->getSpec();
    SDL::Sound::AudioInfo desired;
    desired.format   = destSpec.format;
    desired.channels = destSpec.channels;
    desired.rate     = destSpec.freq;
    
    sample = SDL::Sound::newSampleFromFile(name.c_str(), &desired, BUFFER_SIZE);
    if (!sample)
        throw Exception("Unable to load sound", SDL::Sound::getError());
    
    bufferPos      = 0;
    bufferDecoded  = 0;
    totalPos       = 0;
*/
}

Sound::~Sound()
{
    delete[] samples;
    //SDL::Sound::freeSample(sample);
}

/*
Uint32 Sound::decode(Uint8* dest, Uint32 pos, Uint32 len)
{
    if (totalPos != pos)
    {
        SDL::Sound::seek(sample, pos * (2 * sample->actual.channels * sample->actual.rate:));
	bufferPos = bufferDecoded = 0;
	totalPos = pos;
    }

    Uint32 total = 0;
    bool eof = false;
    
    while (len > 0 && !eof)
    {
	if (bufferDecoded <= 0)
	{
	    bufferPos = 0;
	    bufferDecoded = SDL::Sound::decode(sample);
	    if (bufferDecoded < sample->buffer_size)
                eof = true;
	    length = len < bufferDecoded ? len : bufferDecoded;
	}
	   
        Uint32 length  = len < bufferDecoded ? len : bufferDecoded;
	memcpy(dest, sample->buffer + bufferPos, length);
        
	dest += length;
        
	total += length;
	len  -= length;
		
	bufferPos += length;
	bufferDecoded -= length;

	totalPos += length;
    }
	
    return total;
    
    if (pos + len >= length)
        len = length - pos;
    std::memcpy(dest, samples + pos, len);
    return len;
}
*/
} // namespace Audio
} // namespace Engine

