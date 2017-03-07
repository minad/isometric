#include "Engine/Graphics/Painter.h"
#include "Engine/Graphics/Surface.h"
#include "Engine/Graphics/Color.h"
#include <cassert>

namespace Engine {
namespace Graphics {

namespace {

/*
 * Color mapping
 */

inline void rgb565_to_rgb(Uint32 p, Uint8& r, Uint8& g, Uint8& b)
{
    r = ((((p) & 0xF800) >> 11) << 3);
    g = ((((p) & 0x07E0) >> 5) << 2);
    b = (((p)  & 0x001F) << 3);
}

inline Uint32 rgb_to_rgb565(Uint8 r, Uint8 g, Uint8 b)
{
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

inline void rgba8888_to_rgba(Uint32 p, Uint8& r, Uint8& g, Uint8& b, Uint8& a)
{
    a = p >> 24;
    r = p >> 16;
    g = p >> 8;
    b = p;
}

inline Uint32 rgba_to_rgba8888(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return ((a << 24) | (r << 16) | (g << 8) | b);
}

inline void rgb888_to_rgb(Uint32 p, Uint8& r, Uint8& g, Uint8& b)
{
    r = p >> 16;
    g = p >> 8;
    b = p;
}

inline Uint32 rgb_to_rgb888(Uint8 r, Uint8 g, Uint8 b)
{
    return ((r << 16) | (g << 8) | b);
}

/*
 * Blending
 */

inline void alphaBlend(Uint8 a, Uint8 sR, Uint8 sG, Uint8 sB, Uint8& dR, Uint8& dG, Uint8& dB)
{
    /* 
    if (a == 128)
    {
        dR = (sR + dR) >> 1;
        dG = (sG + dG) >> 1;
        dB = (sB + dB) >> 1;
    }
    else
    {
        dR = dR + (((sR - dR) * a) >> 8);
        dG = dG + (((sG - dG) * a) >> 8);
        dB = dB + (((sB - dB) * a) >> 8);
    }
    */

    dR = dR + (((sR - dR) * a) >> 8);
    dG = dG + (((sG - dG) * a) >> 8);
    dB = dB + (((sB - dB) * a) >> 8);
}

/*
 * Opaque 8 bit drawing routines
 */

#define BPP 1
#define FUNC(name) name##1

#define SET(p, c) \
    (*(Uint8*)(p) = (c))

#define GET(p) \
    *(Uint8*)(p)

#include "DrawFuncs.h"

/*
 * Opaque 16 bit drawing routines
 */

#define BPP 2
#define FUNC(name) name##2

#define SET(p, c) \
    (*(Uint16*)(p) = (c))

#define GET(p) \
    (*(Uint16*)(p))

#include "DrawFuncs.h"

/*
 * Opaque 24 bit drawing routines
 */

#define BPP 3
#define FUNC(name) name##3

#define SET(p, c) \
do { \
    (p)[0] = (c) & 0xFF; \
    (p)[1] = ((c) >> 8) & 0xFF; \
    (p)[2] = ((c) >> 16) & 0xFF; \
} while (0);

#define GET(p) \
    (*(Uint32*)(p) & 0xFFFFFF)

#include "DrawFuncs.h"

/*
 * Opaque 32 bit drawing routines
 */

#define BPP 4
#define FUNC(name) name##4

#define SET(p, c) \
    (*(Uint32*)(p) = (c))

#define GET(p) \
    (*(Uint32*)(p))

#include "DrawFuncs.h"

/*
 * Blended 16 bit drawing routines
 */

#define BPP 2
#define FUNC(name) name##2Blended

#define SET(p, c) \
do { \
    Uint8 sR, sG, sB, dR, dG, dB, a; \
    rgb565_to_rgb(*(Uint16*)(p), dR, dG, dB); \
    rgba8888_to_rgba((c), sR, sG, sB, a); \
    alphaBlend(a, sR, sG, sB, dR, dG, dB); \
    *(Uint16*)(p) = rgb_to_rgb565(dR, dG, dB); \
} while (0); 

#define GET(p) \
    (*(Uint16*)(p))

#include "DrawFuncs.h"

/*
 * Blended 24 bit drawing routines
 */

#define BPP 3
#define FUNC(name) name##3Blended

#define SET(p, c) \
do { \
    Uint8 sR, sG, sB, dR, dG, dB, a; \
    rgb888_to_rgb(*(Uint32*)(p), dR, dG, dB); \
    rgba8888_to_rgba((c), sR, sG, sB, a); \
    alphaBlend(a, sR, sG, sB, dR, dG, dB); \
    (p)[0] = dR; \
    (p)[1] = dG; \
    (p)[2] = dB; \
} while (0);

#define GET(p) \
    (*(Uint32*)(p) & 0xFFFFFF)

#include "DrawFuncs.h"

/*
 * Blended 32 bit drawing routines
 */

#define BPP 4
#define FUNC(name) name##4Blended

#define SET(p, c) \
do { \
    Uint8 sR, sG, sB, dR, dG, dB, a; \
    rgba8888_to_rgba((c), sR, sG, sB, a);\
    rgb888_to_rgb(*(Uint32*)(p), dR, dG, dB); \
    alphaBlend(a, sR, sG, sB, dR, dG, dB); \
    *(Uint32*)(p) = rgb_to_rgb888(dR, dG, dB); \
} while (0);

#define GET(p) \
    (*(Uint32*)(p))

#include "DrawFuncs.h"

/*
 * Drawing functions
 */

struct DrawFuncs
{
    void (*drawPixel)(Surface* s, int x, int y, Uint32 c);
    void (*drawLine)(Surface* s, int x1, int y1, int x2, int y2, Uint32 c);
    void (*drawVLine)(Surface* s, int x, int y1, int y2, Uint32 c);
    void (*drawHLine)(Surface* s, int y, int x1, int x2, Uint32 c);
    void (*drawCircle)(Surface* s, int mx, int my, int r, Uint32 c);
    void (*floodFill)(Surface* s, int x, int y, Uint32 c);
};

#define FUNC_ENTRY(suffix) \
    { drawPixel##suffix, drawLine##suffix, drawVLine##suffix, \
      drawHLine##suffix, drawCircle##suffix, floodFill##suffix }

const DrawFuncs drawFuncsTable[] =
{
    FUNC_ENTRY(1),
    FUNC_ENTRY(2),
    FUNC_ENTRY(3),
    FUNC_ENTRY(4),
    FUNC_ENTRY(1),
    FUNC_ENTRY(2Blended),
    FUNC_ENTRY(3Blended),    
    FUNC_ENTRY(4Blended),
};

#undef FUNC_ENTRY

void updateEdgeBuffer(int edge[], int x1, int y1, int x2, int y2, const int sign)
{
    int xDelta = x2 - x1, yDelta = y2 - y1;
    int xStep = 0, yStep = 0;
    if (xDelta > 0)
        xStep = 1;
    else if (xDelta < 0)
    {
        xStep = -1;
        xDelta = -xDelta;
    }
    if (yDelta > 0)
        yStep = 1;
    else if (yDelta < 0)
    {
        yStep = -1;
        yDelta = -yDelta;
    }
    int xDelta2 = 2 * xDelta, yDelta2 = 2 * yDelta;
    if (yDelta <= xDelta)
    {
        for (int yDec = yDelta2 - xDelta; ; x1 += xStep, yDec += yDelta2)
        {
            if (x1 - edge[y1] < 0 ? -1 : 1 == sign)
	        edge[y1] = x1;
            if (x1 == x2) break;
            if (yDec >= 0)
            {
                yDec -= xDelta2;
                y1 += yStep;
            }
        }
    }
    else
    {
        for (int xDec = xDelta2 - yDelta; ; y1 += yStep, xDec += xDelta2)
        {            
	    if (x1 - edge[y1] < 0 ? -1 : 1 == sign)
	        edge[y1] = x1;
            if (y1 == y2) break;
            if (xDec >= 0)
            {
                xDec -= yDelta2;
                x1 += xStep;
            }
        }
    }
}

} // END: anonymous namespace

void Painter::start(Surface* s)
{
    assert(!surf);
    surf = s;
    updateFuncTable();
    surf->lock();
}

void Painter::end()
{
    if (surf)
    {
        surf->unlock();
        surf = 0;
        drawFuncs = 0;
        color = 0;
        blending = false;
    }
}

void Painter::drawPixel(int x, int y)
{
    assert(surf);
    if (!surf->getClipRect().containsPoint(x, y))
        return;
    ((DrawFuncs*)drawFuncs)->drawPixel(surf, x, y, color);
}

void Painter::drawLine(int x1, int y1, int x2, int y2)
{
    assert(surf);
    if (!surf->getClipRect().clipLine(x1, y1, x2, y2))
        return;
    ((DrawFuncs*)drawFuncs)->drawLine(surf, x1, y1, x2, y2, color);
}

void Painter::drawVLine(int x, int y1, int y2)
{
    assert(surf);

    if (y2 < y1)
        std::swap(y2, y1);    

    Rect clipRect = surf->getClipRect();
    if (x < clipRect.xMin() || x > clipRect.xMax() || y1 > clipRect.yMax() || y2 < clipRect.yMin())
        return; 
    
    ((DrawFuncs*)drawFuncs)->drawVLine(surf, x, std::max(y1, clipRect.yMin()), std::min(y2, clipRect.yMax()), color);
}

void Painter::drawHLine(int y, int x1, int x2)
{
    assert(surf);
    
    if (x2 < x1)
        std::swap(x2, x1);

    Rect clipRect = surf->getClipRect();
    if (y < clipRect.yMin() || y > clipRect.yMax() || x1 > clipRect.xMax() || x2 < clipRect.xMin())
        return;
	    
    ((DrawFuncs*)drawFuncs)->drawHLine(surf, y, std::max(x1, clipRect.xMin()), std::min(x2, clipRect.xMax()), color);
}

void Painter::drawRect(const Rect& r)
{
    drawVLine(r.x, r.y, r.yMax());
    drawVLine(r.xMax(), r.y, r.yMax());
    drawHLine(r.y, r.x, r.xMax());
    drawHLine(r.yMax(), r.x, r.xMax());
}

void Painter::drawRounded(const Rect& rect, int r)
{
    int xa = rect.x + r;
    int xb = rect.xMax() - r;
    int ya = rect.y + r;
    int yb = rect.yMax() - r;

    for (int x = 0, y = r, dec = 3 - 2 * r; x <= y; ++x)
    {
        drawPixel(xb + x, yb + y);
        drawPixel(xb + x, ya - y);
        drawPixel(xa - x, yb + y);
        drawPixel(xa - x, ya - y);
        drawPixel(xb + y, yb + x);
        drawPixel(xb + y, ya - x);
        drawPixel(xa - y, yb + x);
        drawPixel(xa - y, ya - x);

	if (dec >= 0)
            dec += -4 * --y + 4;
        dec += 4 * x + 6;
    }

    drawHLine(rect.y,      xa, xb);
    drawHLine(rect.yMax(), xa, xb);
    drawVLine(rect.x,      ya, yb);
    drawVLine(rect.xMax(), ya, yb);
}

void Painter::drawTriangle(const int x[3], const int y[3])
{
    drawLine(x[0], y[0], x[1], y[1]);
    drawLine(x[1], y[1], x[2], y[2]);
    drawLine(x[2], y[2], x[0], y[0]);
}

void Painter::drawCircle(int mx, int my, int r)
{
    Rect clipRect = surf->getClipRect();
    if (mx >= clipRect.x + r && mx <= clipRect.xMax() - r &&
        my >= clipRect.y + r && my <= clipRect.yMax() - r)
	((DrawFuncs*)drawFuncs)->drawCircle(surf, mx, my, r, color);
    else
    {
        // Very slow mode with clipping
        for (int x = 0, y = r, dec = 3 - 2 * r; x <= y; ++x)
        {
            drawPixel(mx + x, my + y);
	    drawPixel(mx + x, my - y);
	    drawPixel(mx - x, my + y);
	    drawPixel(mx - x, my - y);
            drawPixel(mx + y, my + x);
            drawPixel(mx + y, my - x);
            drawPixel(mx - y, my + x);
            drawPixel(mx - y, my - x);
            if (dec >= 0)
                dec += -4 * --y + 4;
            dec += 4 * x + 6;
        }
    }
}

void Painter::fillRect(Rect rect)
{
    assert(surf);
    
    if (!surf->getClipRect().clipRect(rect))
        return;

    for (int y = rect.y; y < rect.y + rect.h; ++y)
        ((DrawFuncs*)drawFuncs)->drawHLine(surf, y, rect.x, rect.xMax(), color);
}

void Painter::fillRectVGradient(const Rect& rect, Color colorA, Color colorB)
{
    assert(surf);

    Rect clipped = rect;
    if (!surf->getClipRect().clipRect(clipped))
        return;

    float r = colorA.r;
    float g = colorA.g;
    float b = colorA.b;
    float a = colorA.a;
    float rStep = (colorB.r - r) / rect.w;
    float gStep = (colorB.g - g) / rect.w;
    float bStep = (colorB.b - b) / rect.w;
    float aStep = (colorB.a - a) / rect.w;

    int tmp = rect.w - clipped.w;
    r += rStep * tmp;
    g += gStep * tmp;
    b += bStep * tmp;
    a += aStep * tmp;

    for (int x = clipped.x; x < clipped.x + clipped.w; ++x)
    { 
        ((DrawFuncs*)drawFuncs)->drawVLine(surf, x, clipped.y, clipped.y + clipped.h,
	                                        mapColor(Color((int)r, (int)g, (int)b, (int)a)));
        r += rStep;
        g += gStep;
        b += bStep;
        a += aStep;
    }
}

void Painter::fillRectHGradient(const Rect& rect, Color colorA, Color colorB)
{
    assert(surf);

    Rect clipped = rect;
    if (!surf->getClipRect().clipRect(clipped))
        return;		

    float r = colorA.r;
    float g = colorA.g;
    float b = colorA.b;
    float a = colorA.a;
    float rStep = (colorB.r - r) / rect.h;
    float gStep = (colorB.g - g) / rect.h;
    float bStep = (colorB.b - b) / rect.h;
    float aStep = (colorB.a - a) / rect.h;

    int tmp = rect.h - clipped.h;
    r += rStep * tmp;
    g += gStep * tmp;
    b += bStep * tmp;
    a += aStep * tmp;

    for (int y = clipped.y; y < clipped.y + clipped.h; ++y)
    {
        ((DrawFuncs*)drawFuncs)->drawHLine(surf, y, clipped.x, clipped.x + clipped.w,
                                                mapColor(Color((int)r, (int)g, (int)b, (int)a)));
        r += rStep;
        g += gStep;
        b += bStep;
        a += aStep;
    }
}

void Painter::fillRounded(const Rect& rect, int r)
{
    int xa = rect.x + r;
    int xb = rect.xMax() - r;
    int ya = rect.y + r;
    int yb = rect.yMax() - r;

    int oldX = -1, oldY = -1;
    for (int x = 0, y = r, dec = 3 - 2 * r; x <= y; ++x)
    {
        if (oldY != y)
        {
            drawHLine(yb + y, xa - x, xb + x);
            drawHLine(ya - y, xa - x, xb + x);
            oldY = y;
        }

        if (oldX != x)
        {
            if (x != y)
            {
                if (x > 0)
                {
                    drawHLine(yb + x, xa - y, xb + y);
                    drawHLine(ya - x, xa - y, xb + y);
                }
                else
                    drawHLine(yb, xa - y, xb + y);
            }
            oldX = x;
        }        

        if (dec >= 0)
            dec += -4 * --y + 4;
        dec += 4 * x + 6;
    }

    fillRect(Rect(rect.x, ya, rect.w, rect.h - 2 * r));
}

void Painter::fillTriangle(const int x[3], const int y[3])
{
    int min[2048];
    int max[2048];

    for (int i = 0; i < 2048; ++i)
    {
        min[i] = 100000;
        max[i] = -100000;
    }

    int yMin = y[0];
    int yMax = y[2];

    updateEdgeBuffer(min, x[0], y[0], x[1], y[1], -1);
    updateEdgeBuffer(max, x[0], y[0], x[2], y[2], 1);

    for (int y = yMin; y <= yMax; ++y)
        drawHLine(y, min[y], max[y]);
}

void Painter::fillCircle(int mx, int my, int r)
{
    int oldX = -1, oldY = -1;
    for (int x = 0, y = r, dec = 3 - 2 * r; x <= y; ++x)
    {
        if (oldY != y)
	{
	    drawHLine(my + y, mx - x, mx + x);
            drawHLine(my - y, mx - x, mx + x);
	    oldY = y;
	}

	if (oldX != x)
	{
	    if (x != y)
	    {
	        if (x > 0)
		{
	            drawHLine(my + x, mx - y, mx + y);
                    drawHLine(my - x, mx - y, mx + y);
		}
		else
		    drawHLine(my, mx - y, mx + y);
            }
	    oldX = x;
	}

        if (dec >= 0)
            dec += -4 * --y + 4;
        dec += 4 * x + 6;
    }
}

void Painter::floodFill(int x, int y)
{
    if (!surf->getClipRect().containsPoint(x, y))
        return;
    ((DrawFuncs*)drawFuncs)->floodFill(surf, x, y, color);
}

Uint32 Painter::mapColor(Color c) const 
{
    assert(surf);
    if (blending)
        return rgba_to_rgba8888(c.r, c.g, c.b, c.a);
    return c.toUint32(surf->getPixelFormat());
}

void Painter::updateFuncTable()
{
    assert(surf);
    drawFuncs = &(drawFuncsTable[surf->getBPP() - 1 + (blending ? 4 : 0)]);
}

} // namespace Graphics
} // namespace Engine
