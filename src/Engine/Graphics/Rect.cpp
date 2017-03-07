#include "Engine/Graphics/Rect.h"

namespace Engine {
namespace Graphics {

/* This function was ripped from "Tricks of the Windows game programming gurus" 
 * written by Andre Lamothe ISBN: 0-672-31361-8
 * It returns false if the line is totally outside the clipping area and true
 * if the line was successfully clipped
 */
bool Rect::clipLine(int& x1, int& y1, int& x2, int& y2) const
{
// internal clipping codes
#define CODE_C  0x0
#define CODE_N  0x8
#define CODE_S  0x4
#define CODE_E  0x2
#define CODE_W  0x1

#define CODE_NE 0xa
#define CODE_SE 0x6
#define CODE_NW 0x9
#define CODE_SW 0x5

    int xc1 = x1;
    int yc1 = y1;
    int xc2 = x2;
    int yc2 = y2;

    int p1_code = 0;
    int p2_code = 0;

    // determine codes for p1 and p2
    if (y1 < yMin())
        p1_code |= CODE_N;
    else if (y1 > yMax())
    	p1_code |= CODE_S;

    if (x1 < xMin())
 	p1_code |= CODE_W;
    else if (x1 > xMax())
	p1_code |= CODE_E;

    if (y2 < yMin())
  	p2_code |= CODE_N;
    else if (y2 > yMax())
	p2_code |= CODE_S;

    if (x2 < xMin())
  	p2_code |= CODE_W;
    else if (x2 > xMax())
  	p2_code |= CODE_E;

    // try and trivially reject
    if ((p1_code & p2_code))
        return false;

    // test for totally visible, if so leave points untouched
    if (p1_code == 0 && p2_code == 0)
        return true;

    // determine end clip point for p1
    switch (p1_code)
    {
    case CODE_C: 
        break;

    case CODE_N:		
        yc1 = (int) yMin();
        xc1 = (int) (x1 + 0.5 + (yMin() - y1)
                        * (x2 - x1) / (y2 - y1));
        break;

    case CODE_S:
        yc1 = (int) yMax();
        xc1 = (int) (x1 + 0.5 + (yMax()-y1) 
                        * (x2 - x1) / (y2 - y1));
        break;

    case CODE_W:
        xc1 = (int) xMin();
        yc1 = (int) (y1 + 0.5 + (xMin() - x1)
                        * (y2 - y1) / (x2 - x1));
        break;
            
    case CODE_E:
        xc1 = (int) xMax();
        yc1 = (int) (y1 + 0.5 + (xMax() - x1)
                        * (y2 - y1) / (x2 - x1));
        break;

    // these cases are more complex, must compute 2 intersections
    case CODE_NE:
        // north hline intersection
        yc1 = (int) yMin();
        xc1 = (int) (x1 + 0.5 + (yMin() - y1)
                        * (x2 - x1) / (y2 - y1));

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < xMin() || xc1 > xMax())
        {
                        // east vline intersection
                xc1 = (int) xMax();
                yc1 = (int) (y1 + 0.5 + (xMax() - x1)
                                * (y2 - y1) / (x2 - x1));
        }
        break;
    
    case CODE_SE:
        // south hline intersection
        yc1 = (int) yMax();
        xc1 = (int) (x1 + 0.5 + (yMax() - y1)
                        * (x2 - x1) / (y2 - y1));	

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < xMin() || xc1 > xMax())
        {
                // east vline intersection
                xc1 = (int) xMax();
                yc1 = (int) (y1 + 0.5 + (xMax() - x1)
                                * (y2 - y1) / (x2 - x1));
        }
        break;
    
    case CODE_NW:
        // north hline intersection
        yc1 = (int) yMin();
        xc1 = (int) (x1 + 0.5 + (yMin() - y1) 
                        * (x2 - x1) / (y2 - y1));
                
        // test if intersection is valid, of so then done, else compute next
        if (xc1 < xMin() || xc1 > xMax())
        {
                xc1 = (int) xMin();
                yc1 = (int) (y1 + 0.5 + (xMin() - x1)
                                * (y2 - y1) / (x2 - x1));	
        } 
        break;
            
    case CODE_SW:
        // south hline intersection
        yc1 = (int) yMax();
        xc1 = (int) (x1 + 0.5 + (yMax() - y1) 
                        * (x2-x1)/(y2-y1));	

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < xMin() || xc1 > xMax())
        {
                xc1 = (int) xMin();
                yc1 = (int) (y1 + 0.5 + (xMin() - x1)
                                * (y2 - y1) / (x2 - x1));	
        } 
        break;
    }

    // determine clip point for p2
    switch (p2_code)
    {
    case CODE_C: 
        break;

    case CODE_N:
        yc2 = (int) yMin();
        xc2 = (int) (x2 + (yMin() - y2) * (x1 - x2) / (y1 - y2));
        break;

    case CODE_S:
        yc2 = (int) yMax();
        xc2 = (int) (x2 + (yMax() - y2) * (x1 - x2) / (y1 - y2));
        break;

    case CODE_W:
        xc2 = (int) xMin();
        yc2 = (int) (y2 + (xMin() - x2) * (y1 - y2) / (x1 - x2));
        break;

    case CODE_E:
        xc2 = (int) xMax();
        yc2 = (int) (y2 + (xMax() - x2) * (y1 - y2) / (x1 - x2));
        break;

    // these cases are more complex, must compute 2 intersections
    case CODE_NE:
        // north hline intersection
        yc2 = (int) yMin();
        xc2 = (int) (x2 + 0.5 + (yMin() - y2) 
                        * (x1 - x2) / (y1 - y2));

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < xMin() || xc2 > xMax())
        {
                // east vline intersection
                xc2 = (int) xMax();
                yc2 = (int) (y2 + 0.5 + (xMax() - x2) 
                                * (y1 - y2) / (x1 - x2));
        } 
        break;

    case CODE_SE:
        // south hline intersection
        yc2 = (int) yMax();
        xc2 = (int) (x2 + 0.5 + (yMax() - y2) 
                        * (x1 - x2) / (y1 - y2));	

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < xMin() || xc2 > xMax())
        {
                // east vline intersection
                xc2 = (int) xMax();
                yc2 = (int) (y2 + 0.5 + (xMax() - x2)
                                * (y1 - y2) / (x1 - x2));
        } 
        break;

    case CODE_NW:
        // north hline intersection
        yc2 = (int) yMin();
        xc2 = (int) (x2 + 0.5 + (yMin() - y2)
                        * (x1 - x2) / (y1 - y2));

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < xMin() || xc2 > xMax())
        {
                xc2 = (int) xMin();
                yc2 = (int) (y2 + 0.5 + (xMin() - x2)
                                * (y1 - y2) / (x1 - x2));	
        } 
        break;

    case CODE_SW:
        // south hline intersection
        yc2 = (int) yMax();
        xc2 = (int) (x2 + 0.5 + (yMax() - y2) 
                        * (x1 - x2) / (y1 - y2));	

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < xMin() || xc2 > xMax())
        {
                xc2 = (int) xMin();
                yc2 = (int) (y2 + 0.5 + (xMin() - x2)
                                * (y1 - y2) / (x1 - x2));	
        } 
        break;
    }
    
    // do bounds check
    if ((xc1 < xMin()) || (xc1 > xMax()) ||
        (yc1 < yMin()) || (yc1 > yMax()) ||
        (xc2 < xMin()) || (xc2 > xMax()) ||
        (yc2 < yMin()) || (yc2 > yMax()) )
        return false;

    // store vars back
    x1 = xc1;
    y1 = yc1;
    x2 = xc2;
    y2 = yc2;

    return true;

#undef CODE_C  
#undef CODE_N 
#undef CODE_S 
#undef CODE_E 
#undef CODE_W 
#undef CODE_NE 
#undef CODE_SE 
#undef CODE_NW 
#undef CODE_SW 
}

bool Rect::clipRect(SDL::Rect& rect) const
{
    if (rect.x > xMax() || rect.x + rect.w <= x ||
        rect.y > yMax() || rect.y + rect.h <= y)
        return false;
    
    int diff;

    // Clip left
    if ((diff = rect.x - x) < 0)
    {
        rect.x -= diff;
        rect.w += diff;
    }
    
    // Clip right
    if ((diff = rect.x + rect.w - x - w) > 0)
        rect.w -= diff;

    // Clip top
    if ((diff = rect.y - y) < 0)
    {
        rect.y -= diff;
        rect.h += diff;
    }
    
    // Clip bottom
    if ((diff = rect.y + rect.h - y - h) > 0)
        rect.h -= diff;
    
    return true;
}

bool Rect::clipRect(SDL::Rect& dest, SDL::Rect& src) const
{
    if (dest.x > xMax() || dest.x + dest.w <= x ||
        dest.y > yMax() || dest.y + dest.h <= y)
        return false;		    
   
    int diff;
    
    // Clip left
    if ((diff = dest.x - x) < 0)
    {   
        dest.x -= diff;
        src.x  -= diff;
        dest.w += diff;
	src.w  += diff;
    }
    
    // Clip right
    if ((diff = dest.x + dest.w - x - w) > 0)
    {
        dest.w -= diff;
        src.w  -= diff;
    }
    
    // Clip top
    if ((diff = dest.y - y) < 0)
    {
        dest.y -= diff;
        src.y  -= diff;
        dest.h += diff;
	src.h  += diff;
    }
    
    // Clip bottom
    if ((diff = dest.y + dest.h - y - h) > 0)
    {
        dest.h -= diff;
        src.h  -= diff;
    }
    
    return true;
}

} // namespace Graphics
} // namespace Engine

