#include "Engine/Font/FontImage.h"
#include "Engine/Graphics/Color.h"
#include <cmath>

namespace Engine {
namespace Font {

FontImage::FontImage(const std::string& file, const std::string& charset, int charsPerRow)
   : TileSet(file, charsPerRow,
             (int)std::ceil((float)charset.size() / charsPerRow)),
     charset(charset)
{
}

void FontImage::getGlyphMetrics(char ch, int* xMin, int* yMin,
                              int* xMax, int* yMax, int* advance) const
{
    *xMin = 0;
    *xMax = getTileWidth();
    *yMin = 0;
    *yMax = getTileHeight();
    *advance = getTileWidth();
}

void FontImage::getTextSize(const std::string& text, int* w, int* h) const
{
    *w = 0;
    *h = 0;
    int currWidth = 0;
    for (std::string::const_iterator i = text.begin(); i != text.end(); ++i)
    {
        switch (*i)
        {
        case '\n':
        case '\r':
            *h += getTileHeight(); 
	    if (currWidth > *w)
                *w = currWidth;
	    currWidth = 0;
            continue;

        case ' ':
            currWidth += getTileWidth();
            continue;

        case '\t':
            currWidth += 4 * getTileWidth();
            continue;
        }

        if (charset.find(*i) != std::string::npos)
            currWidth += getTileWidth();
    }

    if (currWidth > *w)
        *w = currWidth;
}

Surface* FontImage::renderText(const std::string& text, Color color) const
{
    int w, h;
    getTextSize(text, &w, &h);
    Surface* surf = new Surface(w, h);
    drawText(surf, text, color, 0, 0);
    return surf;
}

void FontImage::drawText(Surface* surface, const std::string& text, Color color, int x, int y) const
{
    int currX = x;
    int currY = y;
    for (std::string::const_iterator i = text.begin(); i != text.end(); ++i)
    {
        switch (*i)
	{
	case '\n':
	case '\r':
	    currY += getTileHeight();
	    currX = x;
	    continue;

	case ' ':
	    currX += getTileWidth();
	    continue;

	case '\t':
	    currX += 4 * getTileWidth();
	    continue;
	}
	
	std::string::size_type n = charset.find(*i);
	if (n == std::string::npos)
	    continue;
	
	draw(n, surface, currX, currY);
	
        currX += getTileWidth();
    }
}

} // namespace Font
} // namespace Engine
