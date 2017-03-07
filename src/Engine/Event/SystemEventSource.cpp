#include "Engine/Event/SystemEventSource.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/MouseMotionEvent.h"
#include "Engine/Event/WindowEvent.h"
#include "Engine/Event/KeyListener.h"
#include "Engine/Event/MouseListener.h"
#include "Engine/Event/MouseMotionListener.h"
#include "Engine/Event/WindowListener.h"
#include "Engine/Util/Logger.h" 

namespace Engine {
namespace Event {

using Util::Logger;

namespace {

MouseEvent::Button sdlToButton(int button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:      return MouseEvent::LEFT;
    case SDL_BUTTON_RIGHT:     return MouseEvent::RIGHT;
    case SDL_BUTTON_MIDDLE:    return MouseEvent::MIDDLE;
    case SDL_BUTTON_WHEELUP:   return MouseEvent::WHEELUP;
    case SDL_BUTTON_WHEELDOWN: return MouseEvent::WHEELDOWN;
    default:                   return MouseEvent::LEFT;
    }
}

} // anonymous namespace

SmartPtr<SystemEventSource> SystemEventSource::instance;

SystemEventSource* SystemEventSource::getInstance()
{
   if (!instance)
        instance = new SystemEventSource();
    return instance;
}

void SystemEventSource::processEvents()
{
    SDL::Event e;
    while (!active)
    {
        SDL::waitEvent(&e);
        handleEvent(e);
    }
        
    while (SDL::pollEvent(&e))
        handleEvent(e);
}

void SystemEventSource::handleEvent(const SDL::Event& e)
{
    switch(e.type) {
    case SDL::ACTIVEEVENT:
    {
        active = e.active.gain == 1;
	LOG_DEBUG(eventLogger, "Window Active Event: gain = " << (int)e.active.gain
                  << ", state = " << (int)e.active.state);
	WindowEvent event(this, 0, 0, active);
        for (std::list<WindowListener*>::iterator i = windowListener.begin();
	     i != windowListener.end(); ++i)
	    (*i)->windowActiveEvent(event);
        break;
    }
    case SDL::KEYDOWN:
    {
	LOG_DEBUG(eventLogger, "Key Down Event: scancode = " << (int)e.key.keysym.scancode
                  << ", unicode = " << (int)e.key.keysym.unicode);
        KeyEvent event(this, e.key.keysym.sym, e.key.keysym.mod, e.key.keysym.unicode, true);
        for (std::list<KeyListener*>::iterator i = keyListener.begin();
	     i != keyListener.end(); ++i)
            (*i)->keyDownEvent(event);
        break;
    }
    case SDL::KEYUP:
    {
	LOG_DEBUG(eventLogger, "Key Up Event: scancode = " << (int)e.key.keysym.scancode
                  << ", unicode = " << (int)e.key.keysym.unicode);
	KeyEvent event(this, e.key.keysym.sym, e.key.keysym.mod, e.key.keysym.unicode, false);
	for (std::list<KeyListener*>::iterator i = keyListener.begin();
	     i != keyListener.end(); ++i)	
            (*i)->keyUpEvent(event);
        break;
    }
    case SDL::MOUSEMOTION:
    {
	LOG_DEBUG(eventLogger, "Mouse Motion Event: x = " << e.motion.x
                  << ", y = " << e.motion.y);
        int buttonState = (e.motion.state & SDL::button(1) ? MouseMotionEvent::LEFT_MASK : 0) |
	                  (e.motion.state & SDL::button(2) ? MouseMotionEvent::MIDDLE_MASK : 0) |
			  (e.motion.state & SDL::button(3) ? MouseMotionEvent::RIGHT_MASK : 0);
        MouseMotionEvent event(this, buttonState, e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
	for (std::list<MouseMotionListener*>::iterator i = mouseMotionListener.begin();
	     i != mouseMotionListener.end(); ++i)
            (*i)->mouseMotionEvent(event);
        break;
    }    
    case SDL::MOUSEBUTTONDOWN:
    {
	LOG_DEBUG(eventLogger, "Mouse Button Down Event: button = " << (int)e.button.button
                  << ", x = " << e.button.x
                  << ", y = " << e.button.y);
	MouseEvent event(this, sdlToButton(e.button.button), e.button.x, e.button.y, true);
	for (std::list<MouseListener*>::iterator i = mouseListener.begin();
	     i != mouseListener.end(); ++i)
	    (*i)->mouseDownEvent(event);
        break;
    }   
    case SDL::MOUSEBUTTONUP: 
    {
	LOG_DEBUG(eventLogger, "Mouse Button Up Event: button = " << (int)e.button.button
                  << ", x = " << e.button.x
                  << ", y = " << e.button.y);
        MouseEvent event(this, sdlToButton(e.button.button), e.button.x, e.button.y, false);
	for (std::list<MouseListener*>::iterator i = mouseListener.begin();
	     i != mouseListener.end(); ++i)
	    (*i)->mouseUpEvent(event);
        break;
    }   
    case SDL::QUIT: 
    {
	LOG_DEBUG(eventLogger, "Window Close Event");
        WindowEvent event(this, 0, 0, true);
	for (std::list<WindowListener*>::iterator i = windowListener.begin();
	     i != windowListener.end(); ++i)
	    (*i)->windowCloseEvent(event);
        break;   
    }
    case SDL::VIDEORESIZE:
    {
	LOG_DEBUG(eventLogger, "Window Resize Event: w = " << e.resize.w
                  << ", h = " << e.resize.h);
        WindowEvent event(this, e.resize.w, e.resize.h, true);
	for (std::list<WindowListener*>::iterator i = windowListener.begin();
	     i != windowListener.end(); ++i)
	    (*i)->windowResizeEvent(event);
        break;
    }
    }
}

} // namespace Event
} // namespace Engine

