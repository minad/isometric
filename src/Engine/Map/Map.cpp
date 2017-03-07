#include "Engine/Map/Map.h"
#include "Engine/Exception.h"
#include "Engine/Graphics/Rect.h"
#include "Engine/Graphics/Surface.h"
#include "Engine/Graphics/Vector2.h"
#include "Engine/Util/Random.h"
#include "Engine/Util/Logger.h"
#include "Engine/Graphics/Display.h"
#include <fstream>
#include <sstream>

namespace Engine {
namespace Map {

using Util::Logger;
using namespace Util::Random;
using Graphics::Rect;
using Graphics::Display;

Map::Map(const std::string& file)
{
    mapWidth = mapHeight = -1;
    
    std::ifstream in(file.c_str());
    
    LOG_INFO(Logger::mainLogger, "Reading map " << file);
   
    while (!in.eof())
    {
        std::string arg;
        in >> arg;

        if (arg == "width")
	{
            in >> mapWidth;
            LOG_INFO(Logger::mainLogger, "Map width: " << mapWidth);
	}
	else if (arg == "height")
	{
            in >> mapHeight;
	    LOG_INFO(Logger::mainLogger, "Map height: " << mapWidth);
	}
        else if (arg == "tileWidth")
        {
            in >> tileWidth;
            LOG_INFO(Logger::mainLogger, "Tile width: " << tileWidth);
        }
        else if (arg == "tileHeight")
        {
            in >> tileHeight;
            LOG_INFO(Logger::mainLogger, "Tile height: " << tileWidth);
        } 
	else if (arg == "tileset")
	{
            std::string name;
            int x, y;
	    in >> name;
	    in >> x;
	    in >> y;
            tile = new TileSet(name, x, y);
	}
	else if (arg == "map")
            break;
    }

    if (mapWidth < 0 || mapHeight < 0)
        throw Exception("Invalid Map File", "No width/height specified");

    map = new Coord[mapHeight * mapWidth];
    memset(map, 0, mapHeight * mapWidth * sizeof (Coord));

    for (int y = 0; y < mapHeight && !in.eof(); ++y)
    {
        for (int x = 0; x < mapWidth && !in.eof(); ++x)
	{
	    int tile;
	    in >> tile;

	    int height;
	    in >> height;
	    
	    map[y * mapWidth + x].tile   = tile;   
	    map[y * mapWidth + x].height = height;
	}
    }

    in.close();
}

Map::~Map()
{
    delete[] map;
}

void Map::draw(Surface* surf, Vector2 pos) const
{
    Vector2 offset(100, 100);

    pos -= offset;

    Vector2 pixelStart(-pos.x % tileWidth - offset.x, -pos.y % tileHeight - offset.y - (tile->getTileHeight() - tileHeight) / 2);
    Vector2 pixelPos = pixelStart;

    pos.x /= tileWidth;
    pos.y /= tileHeight;

    Vector2 mapStart(pos.y - pos.x, pos.y + pos.x);
    Vector2 mapPos = mapStart;
    
    int maxTilesX = 2 * (offset.x + surf->getRect().w / tileWidth);
    int maxTilesY = 2 * (offset.y + surf->getRect().h / tileHeight);

    for (int y = 0; y < maxTilesY; ++y)
    {
        for (int x = 0; x < maxTilesX; ++x)
        {
	    if (mapPos.x >= 0 && mapPos.x < mapWidth && mapPos.y >= 0 && mapPos.y < mapHeight)
	    {
	        Coord* coord = map + mapWidth * mapPos.y + mapPos.x;
	        tile->draw(coord->tile, surf, pixelPos.x, pixelPos.y - coord->height);
            }

            pixelPos.x += tileWidth;
            --mapPos.x;
            ++mapPos.y;
        }

        pixelPos.y += tileHeight / 2;
        pixelPos.x = pixelStart.x;

        if (y & 2 == 2)
            ++mapStart.x;
        else
        {
            pixelPos.x += tileWidth / 2;
            ++mapStart.y;
        }

        mapPos = mapStart;
    }
}

#include "mousemap.h"

void Map::screenToTile(int wx, int wy, int& x, int& y, const Vector2& pos) const
{
    wx += pos.x;
    wy += pos.y;

    // Coarse coords
    int cx = wx / tileWidth;
    int cy = wy / tileHeight;

    std::cout << "cx = " << cx << ", cy = " << cy << std::endl;

    // Fine coordinates
    int fx = wx % tileWidth;
    int fy = wy % tileHeight;

    fy += (tile->getTileHeight() - tileHeight) / 2;
    
    if (fx < 0)
    {
        fx += tileWidth;
        --cx;
    }

    if (fy < 0)
    {
        fy += tileHeight;
        --cy;
    }
    
    //std::cout << "fx = " << fx << ", fy = " << fy << std::endl;
    
    // Coordinates
    x = cy - cx;
    y = cy + cx;

    //std::cout << "x = " << x << ", y = " << y << std::endl;

    int n = 0, height = 0;
    if (x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
    {
        n = map[y * mapWidth + x].tile % 15;
        height = map[y * mapWidth + x].height;
    }

    std::cout << "n = " << n << std::endl;

    int m = mousemap[n * tileWidth + fx + mouseMapWidth * (fy + height)];
    
    switch (m)
    {
    // Northwest
    case 0:
        std::cout << "NW" << std::endl;
        --y;
        fx += tileWidth / 2;
        fy += tileHeight / 2;
        break;
        
    // North
    case 1:   
        std::cout << "N" << std::endl;
        --y;
        --x;
        fy += tileHeight / 2;
        break;
        
    // South
    case 4: 
        std::cout << "S" << std::endl;
        ++y;
        ++x;
        fy -= tileHeight / 2;
        break;
        
    // Southwest
    case 3: 
        std::cout << "SW" << std::endl;
        ++x;
        fx += tileWidth / 2;
        fy -= tileHeight / 2;		
        break;
        
    // Southeast
    case 2: 
        std::cout << "SO" << std::endl;
        ++y;
        fx -= tileWidth / 2;
        fy -= tileHeight / 2;		
        break;

    // Northeast
    case 5:    
        std::cout << "NO" << std::endl;
        --x;
        fx -= tileWidth / 2;
        fy += tileHeight / 2;		
        break;
    }

/*
    int count = 4;
    int oldm = -1;
    while (count > 4 && oldm < 5)
    {
        int n = 0, height = 0;
        if (x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
        {
            n = map[y * mapWidth + x].tile % 15;
            height = map[y * mapWidth + x].height;
        }
 
	int m = mousemap[n * tileWidth + mouseMapWidth * (fy + height) + fx];
	
	int tfy = fy + height;
	if (fx < 0 || tfy < 0 || fx >= tileWidth || tfy >= tileHeight)
	{
	    if (tfy >= tileHeight)
	    {
	        m = 4;
                ++y;
	        ++x;
	        fy -= tileHeight / 2;
	    }
	    oldm = m;
	    continue;
	}
	
	switch (m)
	{
	// Northwest
	case 0:
	    if (oldm == 2)
	        --count;
	    else
	        count = 4;
	    std::cout << "NW" << std::endl;
	    --y;
	    fx += tileWidth / 2;
	    fy += tileHeight / 2;
	    break;
	   
	// North
	case 1:
	    if (oldm == 4)
	        --count;
            else
	        count = 4;	    
	    std::cout << "N" << std::endl;
	    --y;
	    --x;
	    fy += tileHeight / 2;
	    break;
	   
	// South
	case 4:
            if (oldm == 1)
	        --count;
            else
	        count = 4;	    
	    std::cout << "S" << std::endl;
	    ++y;
	    ++x;
	    fy -= tileHeight / 2;
	    break;
	   
	// Southwest
	case 3:
            if (oldm == 5)
	        --count;
            else
	        count = 4;	    
            std::cout << "SW" << std::endl;
	    ++x;
            fx += tileWidth / 2;
	    fy -= tileHeight / 2;		
	    break;
	    
	// Southeast
	case 2:
            if (oldm == 0)
	        --count;
            else
	        count = 4;	    
            std::cout << "SO" << std::endl;
	    ++y;
            fx -= tileWidth / 2;
	    fy -= tileHeight / 2;		
	    break;

        // Northeast
	case 5:
            if (oldm == 3)
	        --count;
            else
	        count = 4;	    
            std::cout << "NO" << std::endl;
	    --x;
            fx -= tileWidth / 2;
	    fy += tileHeight / 2;		
	    break;
	}

	oldm = m;
    }
*/
}

} // namespace Map
} // namespace Engine
