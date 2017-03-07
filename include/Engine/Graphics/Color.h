#ifndef _Engine_Graphics_Color_h
#define _Engine_Graphics_Color_h

#include "SDLWrapper.h" 

namespace Engine {
namespace Graphics {

class Color
{
public:

    Uint8 r, g, b, a;
   
    Color()
        : r(0), g(0), b(0), a(0xFF) {}
   
    Color(const Color& c)
        : r(c.r), g(c.g), b(c.b), a(c.a) {}
        
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF)
        : r(r), g(g), b(b), a(a) {}
    
    bool operator==(const Color& c) const
    {
        return (r == c.r && g == c.g && b == c.b && a == c.a);
    }

    Uint32 toUint32(const SDL::PixelFormat& format) const
    {
        return SDL::mapRGBA(const_cast<SDL::PixelFormat *>(&format), r, g, b, a);
    }

    static const Color WHITE;
    static const Color BLACK;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
};

} // namespace Graphics
} // namespace Engine

#endif // _Engine_Graphics_Color_h

