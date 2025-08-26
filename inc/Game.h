#pragma once
#include "StateManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Player.h"

enum class GameEvent {
    DEBUG_ON,
    DEBUG_OFF,
    QUIT_REQUESTED,
    PAUSE_REQUESTED,
    RESUME_REQUESTED
};

class Game {
public:
    Game();
    ~Game();

    // Global controls
    void init();
    void run();
    void quit();

    void handleGameEvent(GameEvent event) {
        if (event == GameEvent::QUIT_REQUESTED) {
            this->running = false;
        }
        else if (event == GameEvent::PAUSE_REQUESTED) {
            this->stateManager.changeState(GameState::PAUSE_MENU);
        }
    }

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