#pragma once
#include <SDL2/SDL.h>
#include "Logger.h"

class Renderer {
public:
    Renderer(SDL_Window* window) {
        if (!(this->rendrr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
            Logger::logerr("Failed to create renderer: " + std::string(SDL_GetError()));
            this->rendrr = nullptr;
        }
    }
    ~Renderer() {
        if (this->rendrr)
            SDL_DestroyRenderer(this->rendrr);
        this->rendrr = nullptr;
    }

    inline SDL_Color getDrawColor() {
        Uint8 r, g, b, a;
        if (SDL_GetRenderDrawColor(this->rendrr, &r, &g, &b, &a))
            Logger::logerr("Failed to get renderer draw color: " + std::string(SDL_GetError()));
        return (SDL_Color){ r, g, b, a };
    }
    inline void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        if (!SDL_SetRenderDrawColor(this->rendrr, r, g, b, a))
            Logger::logerr("Failed to set renderer draw color: " + std::string(SDL_GetError()));
    }

    void clear();
    void draw();
    void present();

    inline SDL_Renderer* getraw() { return this->rendrr; }

private:
    SDL_Renderer* rendrr;
};
