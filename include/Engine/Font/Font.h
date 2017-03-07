#ifndef _Engine_Font_Font_h
#define _Engine_Font_Font_h

#include "Engine/Base.h"
#include "Engine/Graphics/Color.h"
#include "Engine/Graphics/Surface.h"
#include <string>

namespace Engine {
namespace Font {

using Graphics::Color;
using Graphics::Surface;

class Font : public Base
{
public:
    
    enum Style {
        STYLE_NORMAL    = 0x0,
        STYLE_BOLD      = 0x1,
        STYLE_ITALIC    = 0x2,
        STYLE_UNDERLINE = 0x4,
    };

    virtual ~Font() { }

    // Font style
    virtual Style getStyle() const = 0;
    virtual void setStyle(Style s) = 0;
   
    // Font metrics
    virtual int getHeight() const = 0;
    virtual int getAscent() const = 0;
    virtual int getDescent() const = 0;
    virtual int getLineSpacing() const = 0;
    virtual bool isFixed() const = 0;
    
    virtual void getGlyphMetrics(char ch, int* xMin, int* yMin,
                                 int* xMax, int* yMax, int* advance) const = 0; 
    virtual void getTextSize(const std::string& text, int* w, int* h) const = 0;
    
    // Rendering
    virtual Surface* renderText(const std::string& text, Color color) const = 0;
    virtual void drawText(Surface* surf, const std::string& text, Color color, int x, int y) const = 0; 
};

} // namespace Font
} // namespace Engine

#endif // _Engine_Font_Font_h

