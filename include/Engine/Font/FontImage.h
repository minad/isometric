#ifndef _Engine_Font_FontImage_h
#define _Engine_Font_FontImage_h

#include "Engine/SmartPtr.h"
#include "Engine/Font/Font.h"
#include "Engine/Graphics/TileSet.h"

namespace Engine {
namespace Font {

using Graphics::TileSet;

class FontImage : public Font, private TileSet
{
public:

    FontImage(const std::string& file, const std::string& charset, int charsPerRow);

    // Font style
    Style getStyle() const
    {
       return STYLE_NORMAL; 
    }
    
    void setStyle(Style s) {}

    // Font metrics
    int getHeight() const
    {
        return getTileHeight();
    }
    
    int getAscent() const
    {
        return getHeight();
    }
    
    int getDescent() const
    {
        return 0;
    }
    
    int getLineSpacing() const
    {
        return 0;
    }
    
    bool isFixed() const
    {
        return true;
    }

    void getGlyphMetrics(char ch, int* xMin, int* yMin,
                         int* xMax, int* yMax, int* advance) const;
    
    void getTextSize(const std::string& text, int* w, int* h) const;

    // Rendering (Color is ignored) 
    Surface* renderText(const std::string& text, Color color) const;
    void drawText(Surface* surface, const std::string& text, Color color, int x, int y) const;
    
private:
  
    std::string charset;
};

} // namespace Font
} // namespace Engine

#endif // _Engine_Font_FontImage_h

