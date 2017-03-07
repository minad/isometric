#include "Engine/Font/FontTrueType.h"
#include "Engine/Graphics/Color.h"
#include "Engine/Graphics/Rect.h"
#include "Engine/Util/Logger.h"
#include "Engine/Exception.h"

namespace Engine {
namespace Font {

using Graphics::Rect;
using Graphics::Color;
using Util::Logger;

namespace {

struct TTFInit
{    
    void init()
    {
        if (!SDL::TTF::wasInit() && SDL::TTF::init() < 0)
            throw Exception("Couldn't initialize font system", SDL::TTF::getError());
    }
        
    ~TTFInit()
    {
         if (SDL::TTF::wasInit())
              SDL::TTF::quit();
    }
} ttfInit;

} // anonymous namespace

FontTrueType::FontTrueType(const std::string& name, int size, int index)
{
    ttfInit.init();

    font = SDL::TTF::openFontIndex(name.c_str(), size, index);
    if (!font)
        throw Exception(std::string("Couldn't open font ") + name, SDL::TTF::getError());

    LOG_DEBUG(Logger::mainLogger, "Loading font " << name);
}

Font::Style FontTrueType::getStyle() const
{
    assert(font);

    switch (SDL::TTF::getFontStyle(font))
    {
    case SDL::TTF::STYLE_BOLD:      return STYLE_BOLD;
    case SDL::TTF::STYLE_ITALIC:    return STYLE_ITALIC;
    case SDL::TTF::STYLE_UNDERLINE: return STYLE_UNDERLINE;
    }
    return STYLE_NORMAL;
}

void FontTrueType::setStyle(Font::Style s)
{
    assert(font);
    
    int style;
    switch (s)
    {
    case STYLE_BOLD:      style = SDL::TTF::STYLE_BOLD; break;
    case STYLE_ITALIC:    style = SDL::TTF::STYLE_ITALIC; break;
    case STYLE_UNDERLINE: style = SDL::TTF::STYLE_UNDERLINE; break;
    default:              style = SDL::TTF::STYLE_NORMAL; break;
    }
    SDL::TTF::setFontStyle(font, style);
}

Surface* FontTrueType::renderText(const std::string& text, Color color) const
{
    assert(font);
    
    SDL::Color sdlColor = { color.r, color.g, color.b };
    SDL::Surface* sdlSurface = SDL::TTF::renderText_Solid(font, text.c_str(), sdlColor);
    if (!sdlSurface)
        throw Exception("Couldn't render text", SDL::getError()); 
    return new Surface(sdlSurface);
}

void FontTrueType::drawText(Surface* surface, const std::string& text, Color color, int x, int y) const
{
    assert(font);

    SDL::Color sdlColor = { color.r, color.g, color.b };
    SDL::Surface* surf = SDL::TTF::renderText_Solid(font, text.c_str(), sdlColor);
    if (!surf)
	throw Exception("Couldn't render text", SDL::getError()); 
    Surface src(surf);
    src.incRef();
    surface->blit(&src, src.getRect(), Rect(x, y, src.getWidth(), src.getHeight()));
}

} // namespace Font
} // namespace Engine
