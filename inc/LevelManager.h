#pragma once
#include <nlohmann/json.hpp>
#include <deque>
#include <string>
#include "Level.h"

class LevelManager {
public:
    LevelManager();
    ~LevelManager();

    void init();
    Level loadNextLevel();
    
private:
    std::string pathToLevels;
    std::string currentLevelName;
    Level currentLevelData;
    std::deque<Level> loadedLevels;

    /// @brief Loads a level from a JSON file
    /// @param levelName The name of the level to load
    /// @return The loaded Level object
    Level loadLevel(const std::string& levelName);

    void unloadLevel();
    void unloadLevel(const std::string& levelName);
};
