#ifndef _Engine_Graphics_TileSet_h
#define _Engine_Graphics_TileSet_h

#include "Engine/Base.h"
#include "Engine/SmartPtr.h"
#include <string>

namespace Engine {
namespace Graphics {

class Surface;

class TileSet : public Base
{
public:

    TileSet(const std::string& file, int numTilesX, int numTilesY);
    
    int getNumTiles() const
    {
        return numTiles;
    }

    int getTileWidth() const
    {
        return tileWidth;
    }

    int getTileHeight() const
    {
        return tileHeight;
    }

    void draw(int id, Surface* dest, int x, int y) const;

private:

    SmartPtr<Surface> surf;
    int numTiles, tileWidth, tileHeight;
};

} // namespace Graphics
} // namespace Engine

#endif // _Engine_Graphics_TileSet_h
