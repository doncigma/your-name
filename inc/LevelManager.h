#pragma once
#include <string>
#include <unordered_map>
#include "Level.h"
#include "AssetManager.h"
#include "LevelLoader.h"

namespace ld = LevelLoader;

class LevelManager {
public:
    LevelManager(AssetManager* assetMgr) : assetManager(assetMgr) {
        currentLevelID = levelIDs.begin();

        Level lvl = ld::loadLevel(*currentLevelID, assetManager);
        if (lvl.tiles.empty()) {
            Logger::logerr("LevelManager::LevelManager(): Failed to load level " + *currentLevelID);
        }
        loadedLevels[*currentLevelID] = lvl;
    }
    ~LevelManager() {}

    const Level* getCurrentLevel() { return &loadedLevels[*currentLevelID]; }

    // TODO: finish level loading logic
    // Level loading
    // const Level* loadPreviousLevel() {
    //     if (currentLevelID == levelIDs.begin() ||
    //         loadedLevels.find(*currentLevelID) != loadedLevels.end()) {
    //         return &loadedLevels[*currentLevelID];
    //     }
    //     else {
    //         loadedLevels.erase(*(currentLevelID + 1));
    //         currentLevelID--;
    //         return &(loadedLevels[*currentLevelID] = ld::loadLevel(*currentLevelID, assetManager));
    //     }
    // }

    const Level* loadNextLevel() {
        auto it = loadedLevels.find(*currentLevelID);
        if (currentLevelID == levelIDs.end() - 1 || it != loadedLevels.end()) 
            return &it->second;
        else {
            Level lvl = ld::loadLevel(*currentLevelID, assetManager);
            if (lvl.tiles.empty()) {
                Logger::logerr("LevelManager::loadNextLevel(): Failed to load level " + *currentLevelID);
                return nullptr;
            }
            loadedLevels.erase(*(currentLevelID - 1));
            loadedLevels[*currentLevelID] = lvl;
            currentLevelID++;
            return &loadedLevels[*currentLevelID];
        }
    }
    
private:
    AssetManager* assetManager;
    std::unordered_map<std::string, Level> loadedLevels;
    std::vector<std::string>::iterator currentLevelID;
    // TODO: standardize level IDs
    std::vector<std::string> levelIDs = {
        "test"
    };
};
