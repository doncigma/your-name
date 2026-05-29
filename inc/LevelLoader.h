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
        level.mapWidth = tilemapJson["width"].get<int>();
        level.mapHeight = tilemapJson["height"].get<int>();
        level.tilesetCols = tilesetJson["columns"].get<int>();
        level.tilesetRows = tilemapJson["height"].get<int>();
        level.tileset = assetManager->loadTexture("assets/tilesets/" + levelID + ".png");

        // Build a lookup from tileset tile ID -> properties
        std::unordered_map<int, Tile> tileProps;
        for (auto& t : tilesetJson["tiles"]) {
            if (!t.contains("properties")) continue;

            int id = t["id"].get<int>();

            Tile tile;
            tile.id = id;
            tile.empty = false;
            tile.collidable = false;
            for (auto& prop : t["properties"]) {
                if (prop["name"] == "empty") {
                    tile.empty = prop["value"].get<bool>();
                }
                else if (prop["name"] == "collidable") {
                    tile.collidable = prop["value"].get<bool>();
                }
                // TODO: more props
            }
            tileProps[id] = tile;
        }

        // Pre-allocate tiles for the full map grid
        int totalTiles = level.mapWidth * level.mapHeight;
        level.tiles.resize(totalTiles, Tile{0, true, false});

        // Tiled uses 1-based IDs in tilemap data (firstgid), 0 means empty
        int firstgid = 1;
        if (tilemapJson.contains("tilesets") && !tilemapJson["tilesets"].empty()) {
            firstgid = tilemapJson["tilesets"][0]["firstgid"].get<int>();
        }

        // Fill tiles from tilemap layer data
        for (auto& layer : tilemapJson["layers"]) {
            auto& data = layer["data"];
            for (int i = 0; i < totalTiles && i < static_cast<int>(data.size()); i++) {
                int rawID = data[i].get<int>();
                if (rawID == 0) continue; // Tiled empty cell, can maybe save in array for background cell calc

                int tileID = rawID - firstgid;
                auto it = tileProps.find(tileID);
                if (it != tileProps.end()) {
                    level.tiles[i] = it->second;
                }
                else {
                    // Tile exists in map but has no properties defined
                    level.tiles[i] = Tile{tileID, false, false};
                }
            }
        }

        return level;
    }
};