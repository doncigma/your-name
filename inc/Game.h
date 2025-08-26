#pragma once
#include "GameEvent.h"
#include "InputManager.h"
#include "Player.h"
#include "Renderer.h"
#include "StateManager.h"

class Game {
public:
    Game();
    ~Game();

    // Global controls
    void init();
    void run();
    void quit();

    // Event handling
    void handleGameEvent(GameEvent& event);

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
    StateManager stateManager;
    bool running;
};