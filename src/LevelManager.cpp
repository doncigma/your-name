#include <fstream>
#include <nlohmann/json.hpp>
#include <deque>
#include "LevelManager.h"
#include "Logger.h"

LevelManager::LevelManager() {
    this->currentLevelName = "start";
    this->loadedLevels = std::deque<Level>();
    this->loadLevel(this->currentLevelName);
}

LevelManager::~LevelManager() {
    this->loadedLevels.~deque();
}

Level LevelManager::loadNextLevel() {
    this->unloadPrevLevel();

    this->currentLevelName = this->loadedLevels.back().getName();
    std::string levelPath = "levels/" + this->currentLevelName + ".json";

    std::ifstream file = std::ifstream(levelPath);
    if (!file || !file.is_open()) {
        Logger::log("Failed to open level file: " + levelPath);
        return;
    }

    nlohmann::json levelData;
    file >> levelData;
    file.close();

    std::vector<ObjectData> objects;
    for (const auto& item : levelData["objects"]) {
        ObjectData obj;
        obj.type = item["type"];
        obj.x = item["x"];
        obj.y = item["y"];
        obj.width = item["width"];
        obj.height = item["height"];
        objects.push_back(obj);
    }

    Level level = Level(levelName, levelPath, objects);
    this->loadedLevels.push_back(level);
    this->currentLevelData = level;
    return level;
}

void LevelManager::unloadPrevLevel() {
    if (!loadedLevels.empty())
        loadedLevels.pop_front();
    else Logger::log("LevelManager::unloadLevel(): No levels are currently loaded.");
}
