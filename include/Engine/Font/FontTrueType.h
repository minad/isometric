#ifndef _Engine_Font_FontTrueType_h
#define _Engine_Font_FontTrueType_h

#include "Engine/Font/Font.h"
#include "SDLWrapper.h"
#include <cassert>

namespace Engine {
namespace Font {

class FontTrueType : public Font
{
public:

    FontTrueType(const std::string& name, int size, int index = 0);
    
    ~FontTrueType()
    {
        if (font)
            SDL::TTF::closeFont(font);
    }

    // Name
    std::string getName() const
    {
        assert(font);
        return std::string(SDL::TTF::fontFaceFamilyName(font));
    }

    // Font style
    Style getStyle() const;
    void setStyle(Style s);

    // Font metrics
    int getHeight() const
    {
        assert(font);
        return SDL::TTF::fontHeight(font);
    }
    
    int getAscent() const
    {
        assert(font);
        return SDL::TTF::fontAscent(font);
    }
    
    int getDescent() const
    {
        assert(font);
        return SDL::TTF::fontDescent(font);
    }
    
    int getLineSpacing() const
    {
        assert(font);
        return SDL::TTF::fontLineSkip(font);
    }
    
    bool isFixed() const
    {
        assert(font);
        return SDL::TTF::fontFaceIsFixedWidth(font);
    }

    void getGlyphMetrics(char ch, int* xMin, int* yMin,
                         int* xMax, int* yMax, int* advance) const
    {
        assert(font);
	SDL::TTF::glyphMetrics(font, ch, xMin, xMax, xMax, yMax, advance);
    }
    
    void getTextSize(const std::string& text, int* w, int* h) const
    {
        assert(font);
	SDL::TTF::sizeText(font, text.c_str(), w, h);
    }

    // Rendering 
    Surface* renderText(const std::string& text, Color color) const;
    void drawText(Surface* surface, const std::string& text, Color color, int x, int y) const;
    
private:

    SDL::TTF::Font* font;
};

} // namespace Font
} // namespace Engine

#endif // _Engine_Font_FontTrueType_h

