#ifndef _Engine_Graphics_Rect_h
#define _Engine_Graphics_Rect_h

#include "SDLWrapper.h"

namespace Engine {
namespace Graphics {

class Rect : public SDL::Rect
{
public:

    Rect()
    {
        x = y = w = h = 0;
    }

    Rect(int x, int y, int w, int h)
    { 
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    Rect(const SDL::Rect& r)
    {
        x = r.x;
	y = r.y;
	w = r.w;
	h = r.h;
    }

    int xMin() const
    {
        return x;
    }

    int xMax() const
    {
        return x + w - 1;
    }

    int yMin() const
    {
        return y;
    }

    int yMax() const
    {
        return y + h - 1;
    }

    bool operator==(const SDL::Rect& r) const
    {
        return (x == r.x && y == r.y && w == r.w && h == r.h);
    }

    bool operator!=(const SDL::Rect& r) const
    {
        return !(*this == r);
    }

    bool containsPoint(int x, int y) const
    {
        return (x >= xMin() && x <= xMax() &&
                y >= yMin() && y <= yMax());
    }

    bool clipLine(int& x1, int& y1, int& x2, int& y2) const;

    bool clipRect(SDL::Rect& rect) const;

    // Screen clipping
    bool clipRect(SDL::Rect& dest, SDL::Rect& src) const;
};

} // namespace Graphics
} // namespace Engine

#endif // _Engine_Graphics_Rect_h

