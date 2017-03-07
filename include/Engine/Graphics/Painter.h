#ifndef _Engine_Graphics_Painter_h
#define _Engine_Graphics_Painter_h

#include "Engine/SmartPtr.h"
#include "Engine/Graphics/Surface.h"
#include "Engine/Graphics/Color.h"
#include <boost/noncopyable.hpp>
#include <string>

namespace Engine {
namespace Graphics {

class Rect;

class Painter : boost::noncopyable
{
public:

    Painter()
        : drawFuncs(0), color(0), blending(false) {}

    Painter(Surface* s)
        : drawFuncs(0), color(0), blending(false)
    {
        start(s);
    }

    ~Painter()
    {
        end();
    }

    // Attaches the painter to a surface
    void start(Surface* surf);
    
    // Releases the painter from a surface
    void end();

    void setBlending(bool blend)
    {
        blending = blend;
        updateFuncTable();
    }
    
    bool hasBlending() const
    {
        return blending;
    }

    void setColorIndex(Uint8 c)
    {
        color = c;
    }

    void setColor(Color c)
    {
        color = mapColor(c);
    }
   
    void drawPixel(int x, int y);
    
    void drawLine(int x1, int y1, int x2, int y2);
   
    void drawHLine(int y, int x1, int x2);

    void drawVLine(int x, int y1, int y2);
   
    void drawRect(const Rect& rect);

    void drawRounded(const Rect& rect, int r);

    void drawTriangle(const int x[3], const int y[3]);

    void drawCircle(int x, int y, int r);

    void fillRect(Rect rect);

    void fillRectHGradient(const Rect& rect, Color a, Color b);

    void fillRectVGradient(const Rect& rect, Color a, Color b);

    void fillRounded(const Rect& rect, int r);

    void fillTriangle(const int x[3], const int y[3]);

    void fillCircle(int x, int y, int r);

    void floodFill(int x, int y);

private:

    void updateFuncTable();
    Uint32 mapColor(Color c) const;

    SmartPtr<Surface> surf;
    const void*       drawFuncs;
    Uint32            color;
    bool              blending;
};

} // namespace Graphics
} // namespace Engine

#endif // _Engine_Graphics_Painter_h
