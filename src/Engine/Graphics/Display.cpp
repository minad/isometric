#include "Engine/Graphics/Display.h"
#include "Engine/Exception.h"
#include "Engine/Util/Logger.h"
#include "Engine/Event/SystemEventSource.h"
#include "Engine/Event/WindowEvent.h"
#include "SDLWrapper.h"
#include <string>

namespace Engine {
namespace Graphics {

using Event::SystemEventSource;
using Event::WindowEvent;
using Util::Logger;

namespace {

struct VideoInit
{    
    void init()
    {
        if (!SDL::wasInit(SDL::INIT_VIDEO) &&
            SDL::initSubSystem(SDL::INIT_VIDEO) < 0)
            throw Exception("Couldn't initialize video", SDL::getError());
    }
        
    ~VideoInit()
    {
         if (SDL::wasInit(SDL::INIT_VIDEO))
              SDL::quitSubSystem(SDL::INIT_VIDEO);
    }
} videoInit;

} // anonymous namespace

SmartPtr<Display> Display::instance;

Display::Display()
    : numDirtyRects(0)
{
    videoInit.init();
    
    SystemEventSource::getInstance()->addWindowListener(this);
}

Display::~Display()
{
    SystemEventSource::getInstance()->removeWindowListener(this);
    close();
}

void Display::setMode(int w, int h, bool full)
{
    surf = SDL::setVideoMode(w, h, 0, (full ? SDL::FULLSCREEN : 0) |
                             SDL::ANYFORMAT | SDL::HWSURFACE | SDL::RESIZABLE);
    if (!surf)
        throw Exception("Display mode couldn't be set", SDL::getError());
    
    char name[32];
    SDL::videoDriverName(name, sizeof (name));
    LOG_INFO(Logger::mainLogger, "Display (" << w << 'x' << h << (full ? ", full" : "") << ") opened: " << name);
}

void Display::close()
{
    if (surf)
    {
        try { setFullscreen(false); } catch (...) { }
	SDL::freeSurface(surf);
        surf = 0;
    }
}

void Display::setFullscreen(bool full)
{
    assert(surf);

    surf = SDL::setVideoMode(surf->w, surf->h, surf->format->BitsPerPixel,
               full ? surf->flags | SDL::FULLSCREEN : surf->flags & ~SDL::FULLSCREEN);
    if (!surf)
        throw Exception("Display mode coudn't be changed", SDL::getError());
}

void Display::addDirtyRect(const Rect& rect)
{
    if (numDirtyRects < MAX_DIRTY_RECTS)
    {
        dirtyRects[numDirtyRects] = rect;
	getRect().clipRect(dirtyRects[numDirtyRects]);
	++numDirtyRects;
    }
}

void Display::update()
{
    assert(surf);
   
    if (numDirtyRects == MAX_DIRTY_RECTS)
        SDL::updateRect(surf, 0, 0, getWidth(), getHeight());
    else
        SDL::updateRects(surf, numDirtyRects, dirtyRects);
    numDirtyRects = 0;

    struct timespec time = { 0, 500000 };
    nanosleep(&time, 0);
    //SDL::delay(10);
}

void Display::setWindowTitle(const std::string& title)
{
    SDL::WM::setCaption(title.c_str(), 0);
}

std::string Display::getWindowTitle() const
{
    char* p;
    SDL::WM::getCaption(&p, 0);
    return std::string(p);
}	

void Display::windowResizeEvent(const WindowEvent& event)
{
    assert(surf);

    surf = SDL::setVideoMode(event.width, event.height,
                             surf->format->BitsPerPixel, surf->flags);
    if (!surf)
        throw Exception("Display couldn't be resized", SDL::getError());
}

Display* Display::getInstance()
{
    if (!instance)
        instance = new Display();
    return instance;
}

} // namespace Graphics
} // namespace Engine
