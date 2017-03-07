#ifndef _Engine_Event_SystemEventSource_h
#define _Engine_Event_SystemEventSource_h

#include "Engine/Base.h"
#include "Engine/SmartPtr.h"
#include "Engine/Event/EventSource.h"
#include "Engine/Util/Logger.h"
#include "SDLWrapper.h" 
#include <list>
#include <string>

namespace Engine {
namespace Event {

class KeyListener;
class MouseListener;
class MouseMotionListener;
class WindowListener;

using Util::Logger;

class SystemEventSource : public Base, EventSource
{
public:
	
    void addKeyListener(KeyListener* l)
    {
        keyListener.push_back(l);
    }
    
    void removeKeyListener(KeyListener* l)
    {
        keyListener.remove(l);
    }
    
    void addMouseListener(MouseListener* l)
    {
        mouseListener.push_back(l);
    }
    
    void removeMouseListener(MouseListener* l)
    {
        mouseListener.remove(l);
    }

    void addMouseMotionListener(MouseMotionListener* l)
    {
        mouseMotionListener.push_back(l);
    }
    
    void removeMouseMotionListener(MouseMotionListener* l)
    {
        mouseMotionListener.remove(l);
    }
    
    void addWindowListener(WindowListener* l)
    {
        windowListener.push_back(l);
    }
    
    void removeWindowListener(WindowListener* l)
    {
        windowListener.remove(l); 
    }
    
    void processEvents();
    
    static SystemEventSource* getInstance();
    
private:

    SystemEventSource()
        : active(true), eventLogger(Logger::INFO) {}

    void handleEvent(const SDL::Event& e);
    
    bool active;
    
    Logger eventLogger;

    std::list<KeyListener*>         keyListener;
    std::list<MouseListener*>       mouseListener;
    std::list<MouseMotionListener*> mouseMotionListener;
    std::list<WindowListener*>      windowListener;

    static SmartPtr<SystemEventSource> instance;
};

} // namespace Event
} // namespace Engine 

#endif // _Engine_Event_SystemEventSource_h

