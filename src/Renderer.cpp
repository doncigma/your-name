#include "Renderer.h"

Renderer::Renderer(SDL_Window* window) { 
    this->rendrr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
}
Renderer::~Renderer() { SDL_DestroyRenderer(this->rendrr); }

void Renderer::clear() { 
    SDL_RenderClear(this->rendrr); 
}

void Renderer::present() { 
    SDL_RenderPresent(this->rendrr); 
}
