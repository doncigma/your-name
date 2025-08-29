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
    
    /// @brief Loads a level from a JSON file
    /// @param levelName The name of the level to load
    /// @return The loaded Level object
    Level loadNextLevel();
    
    private:
    std::string pathToLevels;
    std::string currentLevelName;
    Level currentLevelData;
    std::deque<Level> loadedLevels;
    
    void unloadPrevLevel();
};
