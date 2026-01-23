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
    Game() {
        // Rendering
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow("Your Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (!window) {
            Logger::logerr("Failed to create window: " + std::string(SDL_GetError()));
            return;
        }

        renderer = new Renderer(window);
        SDL_Rect view = renderer->getViewport();
        camera = {player.pos.x - view.w / 2, player.pos.y - view.h / 2, view.w, view.h};
        
        // Components
        assetManager = new AssetManager(renderer);
        inputManager = InputManager();
        inputManager.setEventHandler([this](GameEvent event) {
            handleGameEvent(event);
        });
        levelManager = new LevelManager(assetManager);
        currentLevel = levelManager->getCurrentLevel();
        player = Player();

        // State
        stateManager = StateManager();
        running = false;
    }
    ~Game() {
        quit();
    }

    // Main game loop
    void run() {
        running = true;
        lastFrameTime = SDL_GetTicks();
        
        while (running) {
            // Timing
            Uint32 currentTime = SDL_GetTicks();
            delta = (currentTime - lastFrameTime) / 1000.0f;
            lastFrameTime = currentTime;

            // Process input
            processEvent();

            // Update states
            update(delta);

            // Render updates
            render();
        }

        quit();
    }

    // Event handling
    void handleGameEvent(GameEvent& event) {
        if (event.type == GameEventType::QUIT_REQUESTED) {
            running = false;
        }
        else if (event.type == GameEventType::PAUSE_REQUESTED || event.type == GameEventType::RESUME_REQUESTED) {
            stateManager.togglePause();
        }
        else if (event.type == GameEventType::DEBUG_REQUESTED) {
            stateManager.toggleDebug();
        }
        else if (event.type == GameEventType::WINDOW_RESIZED) {
            resizeWindow(event.sdlEvent.window);
        }
    }

private:
    // Render members
    SDL_Window* window;
    Renderer* renderer;
    SDL_Rect camera;

    // Manager members
    AssetManager* assetManager;
    InputManager inputManager;
    LevelManager* levelManager;
    StateManager stateManager;
    
    // State members
    const Level* currentLevel;
    Player player;
    bool running;
    float delta;
    Uint32 lastFrameTime;

    // Rendering methods
    void resizeWindow(const SDL_WindowEvent& event) {
        SDL_SetWindowSize(window, event.data1, event.data2);
        renderer->update();
        resizeCamera();
    }

    void resizeCamera() {
        SDL_Rect view = renderer->getViewport();
        camera = {
            player.pos.x - view.w / 2,
            player.pos.y - view.h / 2,
            view.w,
            view.h
        };
    }

    void render() {
        renderer->clear();
        renderer->draw(currentLevel, camera);
        renderer->present();
    }

    // State methods
    void processEvent() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            inputManager.handleEvent(event);
        }
    }
    
    void update(float delta) {
        player.update(delta, &inputManager);
        renderer->update();
        resizeCamera();
        currentLevel = levelManager->getCurrentLevel();
    }

    // Global controls
    void quit() {
        SDL_DestroyWindow(window);
        SDL_Quit();
        window = nullptr;

        delete renderer;
        delete assetManager;
        delete levelManager;
        renderer = nullptr;
        assetManager = nullptr;
        levelManager = nullptr;
    }
};