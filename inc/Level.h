#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

struct Tile {
    int id; // ID of the tile in the tileset texture
    bool empty;
    bool collidable;
};

class Level {
public:
    inline int getTileWidth() const { return tileWidth; }
    inline int getTileHeight() const { return tileHeight; }
    inline int getMapWidth() const { return mapWidth; }
    inline int getMapHeight() const { return mapHeight; }
    inline int getTilesetRows() const { return tilesetRows; }
    inline int getTilesetCols() const { return tilesetCols; }

    const SDL_Texture* getTileset() const { return tileset; }

    inline Tile getTileAt(int x, int y) const {
        if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight)
            return Tile{0, true, false};
        return tiles[y * mapWidth + x];
    }

    std::string levelID;
    SDL_Texture* tileset = nullptr;
    std::vector<Tile> tiles;
    int tileWidth = 0, tileHeight = 0;
    int mapWidth = 0, mapHeight = 0;
    int tilesetCols = 0, tilesetRows = 0;
};
