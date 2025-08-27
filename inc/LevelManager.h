#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "Level.h"

class LevelManager {
public:
    LevelManager();
    LevelManager(std::string levelName);
    ~LevelManager();

    inline Level loadLevel();
    Level loadLevel(const std::string& levelName);
    void unloadLevel();
    void unloadLevel(const std::string& levelName);

private:
    std::string currentLevelName;
    Level currentLevelData;
    std::vector<Level> loadedLevels;
};
