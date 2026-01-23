#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include "AssetManager.h"
#include "Level.h"
#include "Logger.h"

namespace LevelLoader {
    Level loadLevel(const std::string& levelID, AssetManager* assetManager) {
        std::ifstream file("assets/levels/" + levelID + ".json");
        nlohmann::json data;
        file >> data;

        if (!data.contains("visualLayer")) 
            Logger::logerr("Level " + levelID + " is missing visual layer!");
        if (!data.contains("collisionLayer")) 
            Logger::logerr("Level " + levelID + " is missing collision layer!");
        // TODO: other validations

        Level level;
        level.levelID = levelID;
        level.tileWidth = data["width"];
        level.tileHeight = data["height"];
        level.tilesetCols = data["tilesetCols"];
        level.tileset = assetManager->loadTexture("assets/tilesets/" + levelID + ".png");

        for (const auto& tile : data["visualLayer"])
            level.visualTiles.push_back(tile);
        for (const auto& tile : data["collisionLayer"])
            level.collisionTiles.push_back(tile);

        return level;
    }
};