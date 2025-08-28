#include "Renderer.h"

Renderer::Renderer(SDL_Window* window) {
    if (!(this->rendrr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        Logger::logerr("Failed to create renderer: " + std::string(SDL_GetError()));
        this->rendrr = nullptr;
    }
}

Renderer::~Renderer() {
    if (this->rendrr)
        SDL_DestroyRenderer(this->rendrr);
    this->rendrr = nullptr;
}

inline SDL_Color Renderer::getDrawColor() {
    SDL_Color color;
    if (!(SDL_GetRenderDrawColor(this->rendrr, &color.r, &color.g, &color.b, &color.a)))
        Logger::logerr("Failed to get renderer draw color: " + std::string(SDL_GetError()));
    return color;
}

inline void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (!(SDL_SetRenderDrawColor(this->rendrr, r, g, b, a)))
        Logger::logerr("Failed to set renderer draw color: " + std::string(SDL_GetError()));
}

void Renderer::clear() {
    if (!(SDL_RenderClear(this->rendrr)))
        Logger::logerr("Failed to clear renderer: " + std::string(SDL_GetError()));
}

void Renderer::draw() {
    // SDL_Surface* surface = SDL_LoadBMP("assets/player.bmp");
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(this->rendrr, surface);
    // SDL_Rect dest = {x, y, 32, 32};
    // SDL_RenderCopy(this->rendrr, texture, NULL, &dest);
    // SDL_DestroyTexture(texture);
}

void Renderer::present() { 
    SDL_RenderPresent(this->rendrr); 
}
