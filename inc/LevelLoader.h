#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include "AssetManager.h"
#include "Level.h"
#include "Logger.h"

using json = nlohmann::json;

namespace LevelLoader {
    Level loadLevel(const std::string& levelID, AssetManager* assetManager) {
        // Open and parse tilemap and tileset json files
        std::ifstream file("assets/levels/" + levelID + "/" + levelID + "-tilemap.tmj");
        if (!file.is_open()) {
            Logger::logerr("Failed to open " + levelID + "-tilemap.tmj file :(");
            return Level();
        }
        json tilemapJson = json::parse(file);
        
        std::ifstream file2("assets/levels/" + levelID + "/" + levelID + "-tileset.tsj");
        if (!file2.is_open()) {
            Logger::logerr("Failed to open " + levelID + "-tileset.tsj file :(");
            return Level();
        }
        json tilesetJson = json::parse(file2);
        
        file.close();
        file2.close();
        
        if (!tilemapJson.contains("layers") || tilemapJson["layers"].empty()) {
            Logger::logerr("Level " + levelID + " is missing the tile layer!");
            return Level();
        }
        if (!tilesetJson.contains("tiles") || tilesetJson["tiles"].empty()) {
            Logger::logerr("Level " + levelID + " has an invalid tileset!");
            return Level();
        }
        // TODO: other validations
        Level level;
        level.levelID = levelID;
        level.tileWidth = tilemapJson["tilewidth"].get<int>();
        level.tileHeight = tilemapJson["tileheight"].get<int>();
        level.tilesetCols = tilemapJson["width"].get<int>();
        level.tilesetRows = tilemapJson["height"].get<int>();
        level.tileset = assetManager->loadTexture("assets/tilesets/" + levelID + ".png");
        
        std::vector<int> tmpIDs;
        for (auto& layer : tilemapJson["layers"]) {
            for (auto& id : layer["data"]) {
                tmpIDs.push_back(id.get<int>());
            }
        }
        
        for (auto& tid : tmpIDs) {
            for (auto& t : tilesetJson["tiles"]) {
                auto id = t["id"].get<int>();
                if (tid != id) continue;
                
                Tile tile; 
                tile.id = id;
                for (auto& prop : t["properties"]) {
                    std::istringstream iss;
                    if (prop["name"] == "empty") {
                        // iss.str(prop["value"].get<std::string>());
                        // iss >> std::boolalpha >> tile.empty;
                        // iss.clear();
                        tile.empty = prop["value"];
                    }
                    else if (prop["name"] == "collidable") {
                        iss.str(prop["value"].get<std::string>());
                        iss >> std::boolalpha >> tile.collidable;
                        iss.clear();
                    }
                    // TODO: more props
                }
                level.tiles.push_back(tile);
            }
        }

        return level;
    }
};