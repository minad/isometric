#ifndef _Engine_Graphics_Display_h
#define _Engine_Graphics_Display_h

#include "Engine/SmartPtr.h"
#include "Engine/Graphics/Surface.h"
#include "Engine/Event/WindowListener.h"
#include <string>
#include <list>

namespace Engine {
namespace Graphics {

using Event::WindowListener;
using Event::WindowEvent;

struct Display : public Surface, public WindowListener
{
public:

    virtual ~Display();
   
    void setMode(int w, int h, bool full = false);
    
    void close();
    
    void setFullscreen(bool full);
    
    bool isFullscreen() const
    {
        return (surf->flags & SDL::FULLSCREEN);
    }
   
    void setWindowTitle(const std::string& title);

    std::string getWindowTitle() const;
   
    void update();

    void addDirtyRect(const Rect& rect);

    void windowResizeEvent(const WindowEvent& event);

    static Display* getInstance();

private:

    Display();

    const static int MAX_DIRTY_RECTS = 10;

    Rect dirtyRects[MAX_DIRTY_RECTS];
    int  numDirtyRects;
    static SmartPtr<Display> instance;
};

} // namespace Graphics
} // namespace Engine

#endif // _Engine_Graphics_Display_h

