#ifndef _Engine_GUI_Theme_h
#define _Engine_GUI_Theme_h

#include "Engine/Graphics/Surface.h"

namespace Engine {

namespace GUI {

using Graphics::Surface;

class Widget;

class Theme : public Base 
{
public:

    virtual ~Theme() {}

    virtual void drawBorder(const Widget* widget, Surface* surf) const = 0;
};

class DefaultTheme : public Theme
{
public:

    DefaultTheme() {}
    ~DefaultTheme() {}
    
    void drawBorder(const Widget* widget, Surface* surf) const;
};

} // namespace GUI

} // namespace Engine

#endif // _Engine_GUI_Theme_h
