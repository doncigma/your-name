#include "Renderer.h"

Renderer::Renderer(SDL_Window* window, SDL_Rect viewport) {
    if (!(this->rendrr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        Logger::logerr("Failed to create renderer: " + std::string(SDL_GetError()));
        this->rendrr = nullptr;
    }

    this->viewport = viewport;
    SDL_RenderGetViewport(this->rendrr, &this->viewport);
}

Renderer::~Renderer() {
    if (this->rendrr)
        SDL_DestroyRenderer(this->rendrr);
    this->rendrr = nullptr;
}

void Renderer::update() {
    SDL_RenderGetViewport(this->rendrr, &this->viewport);
}

inline void Renderer::clear() {
    if (!(SDL_RenderClear(this->rendrr)))
        Logger::logerr("Failed to clear renderer: " + std::string(SDL_GetError()));
}

inline void Renderer::draw(SDL_Texture* texture, SDL_Rect& camera) {
    SDL_RenderCopy(this->rendrr, texture, &camera, nullptr);
}

inline void Renderer::present() { 
    SDL_RenderPresent(this->rendrr); 
}
