#include <fstream>
#include <unordered_map>
#include "LevelManager.h"
#include "Logger.h"
#include "Tilemap.h"

LevelManager::LevelManager() {
}

LevelManager::~LevelManager() {
}

void LevelManager::createLevels() {
    using T = TileID;
    loadedLevels["castle"] = createCastleLevel();
}

Map LevelManager::createCastleLevel() {
    return Map {
        tiles = {
            T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::AIR, T::WALL, T::WALL,
            T::WALL, T::WALL, T::GROUND, T::GROUND, T::GROUND, T::GROUND, T::GROUND, T::GROUND, T::GROUND, T::GROUND, T::WALL, T::WALL,
        }
    };
}
