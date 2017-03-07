#include "Engine/Graphics/Surface.h"
#include "Engine/Graphics/Display.h"
#include "Engine/Graphics/Color.h"
#include "Engine/Util/Logger.h"
#include "Engine/Exception.h"
#include "SDLWrapper.h"

namespace Engine {
namespace Graphics {

using Util::Logger;

namespace {

inline void memcpy_pitch(Uint8* dest, Uint8* src, int w, int h, int dpitch, int spitch)
{
    Uint8* destEnd = dest + h * dpitch;
    dpitch -= w;
    spitch -= w;
    while (dest < destEnd)
    {
        Uint8* destEndRow = dest + w;
	while (dest < destEndRow)
            *dest++ = *src++;
        dest += dpitch;
        src  += spitch;
    }
}

}

Surface::Surface(SDL::Surface* surf)
    : surf(surf)
{
    LOG_DEBUG(Logger::mainLogger, "Creating surface " << this << " from SDL surface ");
}

Surface::Surface(const std::string& file)
{
    surf = 0;
    SDL::Surface* imgSurface = SDL::IMG::load(file.c_str());
    if (!imgSurface)
	throw Exception(std::string("Couldn't load image ") + file, SDL::IMG::getError());
    
    surf = SDL::displayFormatAlpha(imgSurface);
    SDL::freeSurface(imgSurface);

    LOG_DEBUG(Logger::mainLogger, "Creating surface " << this << " from file " << file);
}

Surface::Surface(int w, int h)
{
    SDL::Surface* display = Display::getInstance()->surf;
    surf = SDL::createRGBSurface(display->flags, w, h, display->format->BitsPerPixel,
                                 display->format->Rmask, display->format->Gmask,
		                 display->format->Bmask, display->format->Amask);
    if (!surf)
        throw Exception("Couldn't create surface", SDL::getError());

    LOG_DEBUG(Logger::mainLogger, "Creating surface " << this << " (" << w << 'x' << h << ')');
}

Surface::~Surface()
{
    if (surf)
        SDL::freeSurface(surf);
    LOG_DEBUG(Logger::mainLogger, "Destroying surface " << this);
}

void Surface::clear(Uint32 color)
{
    assert(surf);

    SDL_FillRect(surf, 0, color);
}

void Surface::blit(Surface* src, Rect srcRect, Rect destRect, Uint8 alpha)
{
    assert(surf);
    
    //if (!getClipRect().clipRect(destRect, srcRect))
    //    return;
    
    if (alpha != 255)
    {
	SDL::setAlpha(src->surf, SDL::SRCALPHA, alpha);
	SDL::blitSurface(src->surf, &srcRect, surf, &destRect);
	SDL::setAlpha(src->surf, 0, 0);
        return;
    }
   
    //SDL::lowerBlit(src->surf, &srcRect, surf, &destRect);
    SDL::blitSurface(src->surf, &srcRect, surf, &destRect);
}

void Surface::stretchBlit(Surface* src, Rect srcRect, Rect destRect)
{
    assert(surf);

    if (!getRect().clipRect(destRect, srcRect))
        return;

    // It's software stretching --> Lock surfaces
    lock();
    src->lock();
   
    // Use the assembler optimized SDL routine
    SDL::softStretch(src->surf, &srcRect, surf, &destRect);
    
    // Unlock surfaces
    src->unlock();
    unlock();
}

void Surface::fill(Rect destRect, Uint32 color)
{
    assert(surf);
    
    if (!getRect().clipRect(destRect))
        return;
    
    SDL::fillRect(surf, &destRect, color);
}

void Surface::setClipRect(Rect rect)
{
    assert(surf);
    SDL::setClipRect(surf, &rect);
}

void Surface::lock()
{
    assert(surf);
    if (SDL::mustLock(surf))
        SDL::lockSurface(surf);
}

void Surface::unlock()
{
    assert(surf);
    if (SDL::mustLock(surf))
        SDL::unlockSurface(surf);
}

void Surface::readPixelBlock(Uint8* pixel, Rect rect)
{
    if (!getRect().clipRect(rect))
        return;

    lock();
    memcpy_pitch(pixel, getPixels() + getPitch() * rect.y + getBPP() * rect.x,
                 rect.w * getBPP(), rect.h, rect.w * getBPP(), getPitch());
    unlock();
}

void Surface::writePixelBlock(Uint8* pixel, Rect rect)
{
    if (!getClipRect().clipRect(rect))
        return;    

    lock();
    memcpy_pitch(getPixels() + getPitch() * rect.y + getBPP() * rect.x, pixel,
                 rect.w * getBPP(), rect.h, getPitch(), rect.w * getBPP());
    unlock();
}

} // namespace Graphics
} // namespace Engine

