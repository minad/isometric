#ifndef _Engine_Map_Map_h
#define _Engine_Map_Map_h

#include "Engine/Base.h"
#include "Engine/SmartPtr.h"
#include "Engine/Graphics/Vector2.h"
#include "Engine/Graphics/Surface.h"
#include "Engine/Graphics/TileSet.h"
#include "Engine/Graphics/Rect.h"
#include <string>

namespace Engine {
namespace Map {

using Graphics::Surface;
using Graphics::Vector2;
using Graphics::TileSet;
using Graphics::Rect;

class Map : public Base
{
public:

    explicit Map(const std::string& file);
    ~Map();

    void draw(Surface* surf, Vector2 pos) const;

    void screenToTile(int wx, int wy, int& x, int& y, const Vector2& pos) const;

private:

    struct Coord
    {
        int tile;
        int height;
    };

    int mapWidth, mapHeight,
        tileWidth, tileHeight;
    
    Coord*            map;
    SmartPtr<TileSet> tile;
};

} // namespace Map
} // namespace Engine

#endif // _Engine_Map_Map_h

