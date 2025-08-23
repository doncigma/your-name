#pragma once
#include <SDL2/SDL.h>
#include <string>

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void clear();
    void present();

    void loadtexture(std::string path);

    SDL_Renderer* getraw() { return this->rendrr; }

private:
    SDL_Renderer* rendrr;
};
