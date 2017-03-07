#include "Engine/Graphics/TileSet.h"
#include "Engine/Graphics/Rect.h"
#include "Engine/Graphics/Surface.h"

namespace Engine {
namespace Graphics {

TileSet::TileSet(const std::string& file, int numTilesX, int numTilesY)
{
    surf = new Surface(file);
    tileWidth = surf->getWidth() / numTilesX;
    tileHeight = surf->getHeight() / numTilesY;
    numTiles = numTilesX * numTilesY;
}

void TileSet::draw(int n, Surface* dest, int x, int y) const
{
    assert(dest);
    assert(surf);
    assert(n < numTiles);
    
    int numTilesX = surf->getWidth() / tileWidth;
    Rect srcRect(tileWidth * (n % numTilesX), tileHeight * (n / numTilesX), tileWidth, tileHeight);
    Rect destRect(x, y, tileWidth, tileHeight);
    dest->blit(surf, srcRect, destRect);
}

} // namespace Graphics
} // namespace Engine
