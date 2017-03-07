#include "Engine/GUI/Widget.h"
#include "Engine/Graphics/Display.h"
#include <algorithm>

#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)

namespace Engine {

namespace GUI {

using Graphics::Display;

Widget::Widget(const Rect& rect)
{
    init();
    setRect(rect);
}

Widget::~Widget()
{
    if (parent)
        parent->removeChild(this);
}

void Widget::addChild(Widget* widget)
{
    widget->parent = this;
    widget->setRect(widget->rect);
    //children.push_back(SmartPtr<Widget>(widget));
}

void Widget::removeChild(Widget* widget)
{
    widget->parent = 0;
    //children.remove(SmartPtr<Widget>(widget));
}

void Widget::draw()
{
    assert(surf);

    if (!visible)
         return;

    bool invalidateAll = invalid;

    if (invalid)
    {
	surf->fill(visibleRect, bgColor.toUint32(surf->getPixelFormat()));

	paint(surf);

        if (border && theme)
            theme->drawBorder(this, surf);
    
        invalid = false;
    }

    Display::getInstance()->blit(surf, visibleRect, screenRect, alpha);

    for (WidgetList::iterator i = children.begin(); i != children.end(); ++i)
    {   
	if (invalidateAll)
	     (*i)->invalidate();
	(*i)->draw();
    }
}

void Widget::init()
{
    invalid = true;
    visible = true;
    enabled = true;
    focus = true;
    border = false;
    activeBorder = false;
    alpha = 255;
    parent = 0;

    theme = new DefaultTheme();
    caption = "";
}

void Widget::updateRect()
{
    Rect pvr, psr;
    if (parent)
    {
        pvr = parent->visibleRect;
	psr = parent->screenRect;
    }
    else
        pvr = psr = Display::getInstance()->getRect();

    Rect tmpr = rect;
    if (!pvr.clipRect(tmpr))
        tmpr = Rect();

    visibleRect.x = tmpr.x - rect.x;
    visibleRect.y = tmpr.y - rect.y;
    
    screenRect.x = psr.x + tmpr.x;
    screenRect.y = psr.y + tmpr.y;
	
    visibleRect.w = screenRect.w = tmpr.w;
    visibleRect.h = screenRect.h = tmpr.h;

    if (!surf || (rect.w != surf->getWidth() || rect.h != surf->getHeight()))
         surf = new Surface(rect.w, rect.h);
    
    invalidate();

    for (WidgetList::iterator i = children.begin(); i != children.end(); ++i)
        (*i)->updateRect();
}

} // namespace GUI

} // namespace Engine
