#include "Engine/GUI/Theme.h"
#include "Engine/Graphics/Painter.h"
#include "Engine/GUI/Widget.h"

namespace Engine {
namespace GUI {

using Graphics::Painter;

void DefaultTheme::drawBorder(const Widget* widget, Surface* surf) const
{
    assert(widget);
    assert(surf);
    
    Painter p(surf);
    p.setColor(widget->getBorderColor());
    
    /*
    p.drawHLine(0, 1, widget->getWidth() - 2);
    p.drawHLine(widget->getHeight() - 1, 1, widget->getWidth() - 2);
    p.drawVLine(0, 1, widget->getHeight() - 2);
    p.drawVLine(widget->getWidth() - 1, 1, widget->getHeight() - 2);
    //p.drawRect(Rect(0, 0, widget->getWidth() - 1, widget->getHeight() - 1));
    //p.drawRect(Rect(2, 2, widget->getWidth() - 5, widget->getHeight() - 5));
    */
    //p.drawRounded(Rect(0, 0, widget->getWidth() - 1, widget->getHeight() - 1), 3);
    p.end();
}

} // namespace GUI
} // namespace Engine
