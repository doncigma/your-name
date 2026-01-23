#pragma once
#include <SDL2/SDL.h>
#include <vector>

struct Tile {
    int id; // ID of the tile in the tileset texture
    bool empty;
    bool collidable;
};

class Level {
public:
    inline int getTileWidth() const { return tileWidth; }
    inline int getTileHeight() const { return tileHeight; }
    inline int getTilesetCols() const { return tilesetCols; }
    inline int getTilesetRows() const { return tilesetRows; }

    const SDL_Texture* getTileset() const { return tileset; }

    inline const Tile getTileAt(int x, int y) const { return tiles[y * tilesetCols + x]; }

    std::string levelID;
    SDL_Texture* tileset;
    std::vector<Tile> tiles;
    int tileWidth, tileHeight, tilesetCols, tilesetRows;
};
