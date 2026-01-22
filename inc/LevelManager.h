#pragma once
#include <string>
#include <unordered_map>
#include "Level.h"

class LevelManager {
public:
    LevelManager();
    ~LevelManager();

    void createLevels();
    
    Level loadPreviousLevel();
    Level loadNextLevel();
    
private:
    std::unordered_map<std::string, Level> loadedLevels;
    
    Level createCastleLevel();
};
