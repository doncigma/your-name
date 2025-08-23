#pragma once
#include "GameState.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Player.h"

class Game {
public:
    Game();
    ~Game();

    // Global controls
    void init();
    void run();
    void quit();

private:
    // Rendering
    void update();
    void render();

    Renderer* renderer;
    SDL_Window* window;
    
    // Game components
    InputManager inputManager;
    Player player;

    // State
    GameState state;
    bool running;
};