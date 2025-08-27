#include "Renderer.h"

void Renderer::clear() {
    if (!(SDL_RenderClear(this->rendrr)))
        Logger::logerr("Failed to clear renderer: " + std::string(SDL_GetError()));
}

void Renderer::draw() {
    SDL_SetRenderDrawColor(this->rendrr, 255, 255, 255, 255);
    SDL_RenderDrawPoint(this->rendrr, 100, 100);
}

void Renderer::present() { 
    SDL_RenderPresent(this->rendrr); 
}
