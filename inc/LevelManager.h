#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include "Tilemap.h"

class LevelManager {
public:
    LevelManager();
    ~LevelManager();

    void createLevels();
    
    Map getMap();
    
private:
    std::unordered_map<std::string, Map> loadedLevels;
    
    Map createCastleLevel();
};
