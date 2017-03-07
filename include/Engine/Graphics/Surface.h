#ifndef _Engine_Graphics_Surface_h
#define _Engine_Graphics_Surface_h

#include "Engine/Base.h"
#include "Engine/Graphics/Rect.h"
#include "SDLWrapper.h" 
#include <cassert>
#include <string>

namespace Engine {
namespace Graphics {

class Color;

class Surface : public Base 
{
public:
   
    Surface(SDL::Surface* surf);
    Surface(int w, int h); 
    explicit Surface(const std::string& file);
    ~Surface();

    void clear(Uint32 color = 0);

    void blit(Surface* src, Rect srcRect, Rect destRect, Uint8 alpha = 255);
    
    void fill(Rect destRect, Uint32 color);

    void stretchBlit(Surface* src, Rect srcRect, Rect destRect);

    int getBPP() const
    {
        assert(surf);
	return surf->format->BytesPerPixel;
    }

    int getWidth() const
    {
        assert(surf);
        return surf->w;
    }
    
    int getHeight() const
    {
        assert(surf);
        return surf->h;
    }
   
    // Convenience method
    Rect getRect() const
    {
        return Rect(0, 0, getWidth(), getHeight());
    }

    Rect getClipRect() const
    {
        assert(surf);
	return Rect(surf->clip_rect);
    }

    void setClipRect(Rect rect);
  
    const SDL::PixelFormat& getPixelFormat() const
    {
        return *(surf->format);
    }

    void lock();

    void unlock();

    int getPitch() const
    {
        assert(surf);
        return surf->pitch;
    }

    Uint8* getPixels()
    {
        assert(surf);
        return (Uint8*)surf->pixels;
    }

    // Read pixel block in the format of the surface
    void readPixelBlock(Uint8* pixel, Rect rect);
    
    // Write pixel block in the format of the surface
    void writePixelBlock(Uint8* pixel, Rect rect);	

protected:
   
    Surface()
        : surf(0) { }
   
    SDL::Surface* surf;
};

} // namespace Graphics
} // namespace Engine

#endif // _Engine_Graphics_Surface_h

