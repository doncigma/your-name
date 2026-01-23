#pragma once
#include <SDL2/SDL.h>
#include <vector>

// Corresponds to collision tiles
enum class TileCollisionID {
    EMPTY = 0,
    SOLID = 1
};

// Corresponds to visual tiles
enum class TileSpriteID {
    EMPTY = 0,
    WALL = 1,
    FLOOR = 2
};

class Level {
public:
    inline int getTileWidth() const { return tileWidth; }
    inline int getTileHeight() const { return tileHeight; }
    inline int getTilesetCols() const { return tilesetCols; }

    const SDL_Texture* getTileset() const { return tileset; }

    inline int getVisualTileAt(int x, int y) const { return visualTiles[y * tilesetCols + x]; }
    inline int getCollisionTileAt(int x, int y) const { return collisionTiles[y * tilesetCols + x]; } 

    std::string levelID;
    SDL_Texture* tileset;
    std::vector<int> visualTiles;
    std::vector<int> collisionTiles;
    int tileWidth, tileHeight, tilesetCols;
};
