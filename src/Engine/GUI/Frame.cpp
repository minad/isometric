#include "Engine/GUI/Frame.h"
#include "Engine/Graphics/Painter.h"

namespace Engine {

namespace GUI {

using Graphics::Painter;

void Frame::paint(Surface* surf)
{
    if (!captionSurf)
        captionSurf = getFont()->renderText(getCaption(), Color::WHITE);
    
    Painter p(surf);
    p.fillRectHGradient(Rect(3, 3, getWidth() - 6, 10), Color(0, 0, 255), Color(0, 0, 128));
    p.fillRectHGradient(Rect(3, 10, getWidth() - 6, 10), Color(0, 0, 128), Color(0, 0, 255)); 
    p.setColor(Color::WHITE);
    p.drawLine(3, 3, 17, 17);
    p.drawLine(17, 3, 3, 17);
    p.drawRect(Rect(3, 3, 14, 14));
    p.end();

    surf->blit(captionSurf, captionSurf->getRect(),
               Rect(30, 2, captionSurf->getWidth(), captionSurf->getHeight()));
}

} // namespace GUI

} // namespace Engine
