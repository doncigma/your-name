#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>

enum class TileType {
    EMPTY,
    SOLID
};

enum class TileID {
    EMPTY = 0,
    WALL,
    FLOOR
};

class Level {
public:
    Level() {}
    ~Level() {}

    inline int getTileWidth() { return this->tileWidth; }
    inline int getTileHeight() { return this->tileHeight; }
    inline int getTilesetCols() { return this->tilesetCols; }

    SDL_Texture* getTileset() { return this->tileset; }

    inline std::vector<int>& getVisualTiles() { return this->visualTiles; }
    inline int getVisualTileAt(int x, int y) { return this->visualTiles[y * this->tilesetCols + x]; }
    inline std::vector<int>& getCollisionTiles() { return this->collisionTiles; }
    inline int getCollisionTileAt(int x, int y) { return this->collisionTiles[y * this->tilesetCols + x]; }

private:
    SDL_Texture* tileset;
    std::vector<int> visualTiles;
    std::vector<int> collisionTiles;
    int tileWidth, tileHeight, tilesetCols;
};
