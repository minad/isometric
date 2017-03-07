#ifndef _Engine_GUI_Widget_h
#define _Engine_GUI_Widget_h

#include "Engine/Base.h"
#include "Engine/SmartPtr.h"
#include "Engine/Event/EventSource.h"
#include "Engine/Event/PropertyChangeListener.h"
#include "Engine/Graphics/Rect.h"
#include "Engine/Graphics/Surface.h"
#include "Engine/GUI/Theme.h"
#include "Engine/Font/Font.h"
#include "Engine/Graphics/Color.h"
#include <list>

namespace Engine {
namespace GUI {

using Event::EventSource;
using Event::PropertyChangeListener;
using Graphics::Rect;
using Graphics::Surface;
using Graphics::Color;
using Font::Font;

class Widget : public Base, EventSource
{
public:

    Widget(const Rect& rect);
    virtual ~Widget();

    const Rect& getRect() const
    {
        return rect;
    }

    void setRect(const Rect& r)
    {
        rect = r;
	updateRect();
    }
    
    int getX() const
    {
        return rect.x;
    }

    void setX(int x)
    {
        rect.x = x;
	updateRect();
    }

    int getY() const
    {
        return rect.y;
    }

    void setY(int y)
    {
        rect.y = y;
	updateRect();
    }
    
    void setPos(int x, int y)
    {
        rect.x = x;
	rect.y = y;
	updateRect();
    }

    int getWidth() const
    {
        return rect.w;
    }

    void setWidth(int w)
    {
        rect.w = w;
	updateRect();
    }

    int getHeight() const
    {
        return rect.h;
    }

    void setHeight(int h)
    {
        rect.h = h;
	updateRect();
    }		    

    void setSize(int w, int h)
    {
        rect.w = w;
	rect.h = h;
	updateRect();
    }

    const Rect& getOffsetRect() const
    {
        return offsetRect;
    }

    void setOffsetRect(const Rect& rect)
    {
        offsetRect = rect;
    }

    void setVisible(bool v)
    {
        visible = v;
        invalidate();
    }

    bool isVisible() const
    {
        return visible;
    }

    bool hasFocus() const
    {
        return focus;
    }

    bool isEnabled() const
    {
        return enabled;
    }

    void setEnabled(bool e)
    {
        enabled = e;
	invalidate();
    }

    bool hasBorder() const
    {
        return border;
    }

    void setBorder(bool b)
    {
        border = b;
	invalidate();
    }

    bool hasActiveBorder() const
    {
        return activeBorder;
    }

    void setActiveBorder(bool a)
    {
        activeBorder = a;
    }

    const std::string& getCaption() const
    {
        return caption;
    }

    void setCaption(const std::string& c)
    {
        caption = c;
	invalidate();
    }

    Color getFgColor() const
    {
        return fgColor;
    }

    void setFgColor(Color color)
    {
        fgColor = color;
	invalidate();
    }

    Color getBgColor() const
    {
        return bgColor;
    }

    void setBgColor(Color color)
    {
        bgColor = color;
	invalidate();
    }

    Color getBorderColor() const
    {
        return borderColor;
    }

    void setBorderColor(Color color)
    {
        borderColor = color;
	invalidate();
    }

    Uint8 getAlpha() const
    {
        return alpha;
    }

    void setAlpha(Uint8 a)
    {
        alpha = a;
	invalidate();
    }

    const Font* getFont() const
    {
        return font;
    }

    void setFont(Font* f)
    {
        font = f;
	invalidate();
    }

    Theme* getTheme() const
    {
        return theme;
    }

    void setTheme(Theme* t)
    {
        theme = t;
	invalidate();
    }

    Widget* getParent() const
    {
        return parent;
    }
    
    void addChild(Widget* widget);
    void removeChild(Widget* widget);

    void addPropertyChangeListener(PropertyChangeListener* l)
    {
        pclistener.push_back(l);
    }
    
    void removePropertyChangeListener(PropertyChangeListener* l)
    {
        pclistener.remove(l);
    }

    void invalidate()
    {
        invalid = true;
    }

    void draw();
   
protected:

    virtual void paint(Surface* surf) {}

    void firePropertyChange(const std::string& p);

private:

    void init();

    void updateRect();

    bool invalid      : 1,
         visible      : 1,
         enabled      : 1,
	 focus        : 1,
	 border       : 1,
         activeBorder : 1;
    
    std::string caption;
    Color  fgColor, bgColor, borderColor;
    Uint8  alpha;
    SmartPtr<Font>    font;
    SmartPtr<Theme>   theme;
    SmartPtr<Surface> surf;

    Rect rect,        // Rechteck im Parent-Widget
         visibleRect, // Sichtbares Teilrechteck im rect
	 screenRect,  // Rechteck auf dem Bildschirm
         offsetRect;  // Offset (left/top/right/bottom)
	 
    Widget* parent;
    
    typedef std::list<PropertyChangeListener*> PCListener;
    PCListener pclistener;
    
    typedef std::list<SmartPtr<Widget> > WidgetList;
    WidgetList children;
};

} // namespace GUI
} // namespace Engine

#endif // _Engine_GUI_Widget_h
