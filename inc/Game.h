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

        // Components
        assetManager = new AssetManager(renderer);
        inputManager.setEventHandler([this](GameEvent event) {
            handleGameEvent(event);
        });

        levelManager = new LevelManager(assetManager);
        currentLevel = levelManager->getCurrentLevel();
        if (!currentLevel) {
            Logger::logerr("Game::Game(): Failed to get current level!");
            quit();
            return;
        }

        // Camera centered on player
        SDL_Rect view = renderer->getViewport();
        camera = {player.pos.x - view.w / 2, player.pos.y - view.h / 2, view.w, view.h};
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
    void handleGameEvent(const GameEvent& event) {
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
    SDL_Window* window = nullptr;
    Renderer* renderer = nullptr;
    SDL_Rect camera = {0, 0, 0, 0};

    // Manager members
    AssetManager* assetManager = nullptr;
    InputManager inputManager;
    LevelManager* levelManager = nullptr;
    StateManager stateManager;

    // State members
    const Level* currentLevel = nullptr;
    Player player;
    bool running = false;
    float delta = 0.0f;
    Uint32 lastFrameTime = 0;

    // Rendering methods
    void resizeWindow(const SDL_WindowEvent& event) {
        SDL_SetWindowSize(window, event.data1, event.data2);
        renderer->update();
        resizeCamera();
    }

    void resizeCamera() {
        SDL_Rect view = renderer->getViewport();
        camera.w = view.w;
        camera.h = view.h;
        camera.x = player.pos.x - view.w / 2;
        camera.y = player.pos.y - view.h / 2;

        // Clamp to map bounds (center if map is smaller than viewport)
        if (currentLevel) {
            int mapPixelW = currentLevel->getMapWidth() * currentLevel->getTileWidth();
            int mapPixelH = currentLevel->getMapHeight() * currentLevel->getTileHeight();

            if (mapPixelW <= camera.w) {
                camera.x = -(camera.w - mapPixelW) / 2;
            } else {
                if (camera.x < 0) camera.x = 0;
                if (camera.x + camera.w > mapPixelW) camera.x = mapPixelW - camera.w;
            }

            if (mapPixelH <= camera.h) {
                camera.y = -(camera.h - mapPixelH) / 2;
            } else {
                if (camera.y < 0) camera.y = 0;
                if (camera.y + camera.h > mapPixelH) camera.y = mapPixelH - camera.h;
            }
        }
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
        if (!window) return; // already cleaned up

        delete levelManager;
        delete assetManager;
        delete renderer;
        levelManager = nullptr;
        assetManager = nullptr;
        renderer = nullptr;

        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_Quit();
    }
};