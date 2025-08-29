#pragma once
#include "AssetManager.h"
#include "GameEvent.h"
#include "InputManager.h"
#include "LevelManager.h"
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
    Renderer* renderer;
    SDL_Window* window;
    SDL_Rect camera;

    void resizeWindow(const SDL_WindowEvent& event);
    void resizeCamera();
    void render();

    // Game components
    AssetManager assetManager;
    InputManager inputManager;
    LevelManager levelManager;
    Player player;

    // State
    StateManager stateManager;
    bool running;
    float delta;
    Uint32 lastFrameTime;

    void processInput();
    void update(float delta);
};