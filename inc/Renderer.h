#pragma once
#include <SDL2/SDL.h>
#include "Logger.h"

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    // Render config
    inline SDL_Color getDrawColor();
    inline void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    
    // Rendering
    inline SDL_Renderer* getraw() { return this->rendrr; }

    void clear();
    void draw();
    void present();

private:
    SDL_Renderer* rendrr;
};
