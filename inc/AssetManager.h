#pragma once
#include <memory>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>
#include <fstream>
#include "Renderer.h"

class AssetManager {
public:
    AssetManager(Renderer* rendrr) : renderer(rendrr) {}
    ~AssetManager() {
        // Free all loaded textures
        for (auto& pair : textures) {
            SDL_DestroyTexture(pair.second);
        }
        textures.clear();
    }

    void unloadTexture(const std::string& path) {
        auto it = textures.find(path);
        if (it != textures.end()) {
            SDL_DestroyTexture(it->second);
            textures.erase(it);
        }
    }
    
    SDL_Texture* loadTexture(const std::string& path) {
        SDL_Texture* tileset = IMG_LoadTexture(renderer->getSDLRenderer(), path.c_str());
        if (!tileset) {
            Logger::logerr("Failed to load texture: " + path + " Error: " + std::string(SDL_GetError()));
            return nullptr;
        }

        textures[path] = tileset;
        return tileset;
    }

private:
    // Map of filepaths to already loaded textures
    std::unordered_map<std::string, SDL_Texture*> textures;

    Renderer* renderer;
};