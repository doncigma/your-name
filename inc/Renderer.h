#pragma once
#include <SDL2/SDL.h>
#include "Logger.h"

class Renderer {
public:
    Renderer(SDL_Window* window, SDL_Rect viewport);
    ~Renderer();

    // Render state
    inline SDL_Rect getViewport() { return this->viewport; };
    void update();

    // Rendering

    inline void clear();
    inline void draw(SDL_Texture* texture, SDL_Rect& camera);
    inline void present();

private:
    SDL_Renderer* rendrr;
    SDL_Rect viewport;
};
