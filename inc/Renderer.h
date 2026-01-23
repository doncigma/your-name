#pragma once
#include <SDL2/SDL.h>
#include "Logger.h"
#include "Level.h"

class Renderer {
public:
    Renderer(SDL_Window* window) {
        if (!(sdlRendrr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
            Logger::logerr("Failed to create renderer: " + std::string(SDL_GetError()));
            sdlRendrr = nullptr;
        }
        
        SDL_RenderGetViewport(sdlRendrr, &viewport);
    }
    ~Renderer() {
        if (sdlRendrr)
            SDL_DestroyRenderer(sdlRendrr);
        sdlRendrr = nullptr;
    }

    SDL_Renderer* getSDLRenderer() { return sdlRendrr; }

    // Rendering
    inline void clear() {
        if (!(SDL_RenderClear(sdlRendrr)))
            Logger::logerr("Failed to clear renderer: " + std::string(SDL_GetError()));
    }

    void draw(const Level* level, SDL_Rect& camera) {
        int tileWidth = level->getTileWidth();
        int tileHeight = level->getTileHeight();

        // Calculate which tiles are visible
        int startX = camera.x / tileWidth;
        int startY = camera.y / tileHeight;
        int endX = (camera.x + camera.w) / tileWidth + 1; // +1 to exclude end in the loop
        int endY = (camera.y + camera.h) / tileHeight + 1;

        // Render only visible tiles
        for (int y = startY; y < endY; y++) {
            for (int x = startX; x < endX; x++) {
                int tileID = level->getVisualTileAt(x, y);
                if (tileID == static_cast<int>(TileSpriteID::EMPTY)) continue;

                // Calculate source rect in tileset
                SDL_Rect src = {
                    (tileID % level->getTilesetCols()) * tileWidth,
                    (tileID / level->getTilesetCols()) * tileHeight,
                    tileWidth,
                    tileHeight
                };
                
                // Calculate destination on screen
                SDL_Rect dst = {
                    x * tileWidth - camera.x,
                    y * tileHeight - camera.y,
                    tileWidth,
                    tileHeight
                };
                
                SDL_RenderCopy(sdlRendrr, level->tileset, &src, &dst);
            }
        }
    }

    inline void present() { SDL_RenderPresent(sdlRendrr); }

    // Render state
    inline SDL_Rect getViewport() { return viewport; };
    
    void update() { 
        SDL_RenderGetViewport(sdlRendrr, &viewport); 
    }

private:
    SDL_Renderer* sdlRendrr;
    SDL_Rect viewport;
};
