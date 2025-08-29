#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>

enum class TileType {
    AIR,
    SOLID
};

enum class TileID {
    AIR,
    WAL,
    FLR,
    STR
};

struct Tile {
    TileType type;
    TileID id;
};

typedef struct Structure {
    int width = 16, height = 16;
    std::vector<TileID> tiles;
} Structure;

Structure staircase {
    .tiles = {
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::AIR, TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR,
        TileID::STR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR, TileID::FLR
    }
};

struct Room {
    int width = 3 * 3, height = 3 * 3;
    std::vector<Structure> structures;
};

class Map {
public:
    Map() {}
    ~Map() {}

    std::vector<Room> rooms;
    SDL_Texture* tileset;
    int tileWidth = 32, tileHeight = 32;
    int tilesetCols = 16; // tiles per row in tileset
};
