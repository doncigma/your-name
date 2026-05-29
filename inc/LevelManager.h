#pragma once
#include <memory>
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

        auto lvl = std::make_unique<Level>(ld::loadLevel(*currentLevelID, assetManager));
        if (lvl->tiles.empty()) {
            Logger::logerr("LevelManager::LevelManager(): Failed to load level " + *currentLevelID);
        }
        loadedLevels[*currentLevelID] = std::move(lvl);
    }
    ~LevelManager() {}

    const Level* getCurrentLevel() { return loadedLevels[*currentLevelID].get(); }

    // TODO: finish level loading logic
    // Level loading
    // const Level* loadPreviousLevel() { ... }

    const Level* loadNextLevel() {
        auto it = loadedLevels.find(*currentLevelID);
        if (currentLevelID == levelIDs.end() - 1 || it != loadedLevels.end())
            return it->second.get();
        else {
            auto lvl = std::make_unique<Level>(ld::loadLevel(*currentLevelID, assetManager));
            if (lvl->tiles.empty()) {
                Logger::logerr("LevelManager::loadNextLevel(): Failed to load level " + *currentLevelID);
                return nullptr;
            }
            loadedLevels.erase(*(currentLevelID - 1));
            loadedLevels[*currentLevelID] = std::move(lvl);
            currentLevelID++;
            return loadedLevels[*currentLevelID].get();
        }
    }

private:
    AssetManager* assetManager;
    std::unordered_map<std::string, std::unique_ptr<Level>> loadedLevels;
    std::vector<std::string>::iterator currentLevelID;
    // TODO: standardize level IDs
    std::vector<std::string> levelIDs = {
        "test"
    };
};
