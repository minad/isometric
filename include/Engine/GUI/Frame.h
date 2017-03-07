#ifndef _Engine_GUI_Frame_h
#define _Engine_GUI_Frame_h

#include "Engine/GUI/Widget.h"

namespace Engine {

namespace GUI {

class Frame : public Widget
{
public:

    Frame(const Rect& rect)
        : Widget(rect) {}

    void paint(Surface* surf);

    bool isActive() const
    {
        return active;
    }

private:

    bool active;

    SmartPtr<Surface> captionSurf;
};

} // namespace GUI

} // namespace Engine

#endif // _Engine_GUI_Frame_h
