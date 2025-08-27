#include "LevelManager.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "Logger.h"

LevelManager::LevelManager() {
    this->currentLevelName = "Start";
    this->loadedLevels = std::vector<Level>();
}

LevelManager::LevelManager(std::string levelName) {
    this->currentLevelName = levelName;
    this->loadedLevels = std::vector<Level>();
}

LevelManager::~LevelManager() {
    this->loadedLevels.clear();
}

/// @brief Loads the current level
/// @return The loaded Level object
inline Level LevelManager::loadLevel() {
    return (this->currentLevelData = this->loadLevel(this->currentLevelName));
}

/// @brief Loads a level from a JSON file
/// @param levelName The name of the level to load
/// @return The loaded Level object
Level LevelManager::loadLevel(const std::string& levelName) {
    std::string levelPath = "levels/" + levelName + ".json";

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
    return level;
}

void LevelManager::unloadLevel() {
    if (!loadedLevels.empty())
        loadedLevels.pop_back();
    else Logger::log("LevelManager::unloadLevel(): No levels are currently loaded.");
}

void LevelManager::unloadLevel(const std::string& levelName) {
    auto it = std::find_if(
        loadedLevels.begin(),
        loadedLevels.end(),
        [&levelName](const Level& lvl) { return lvl.getName() == levelName; }
    );
        
    if (it != loadedLevels.end())
        loadedLevels.erase(it);
    else Logger::log("LevelManager::unloadLevel(const std::string&): Level not found: " + levelName);
}
