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
    }
    ~Game() {
        quit();
    }

    // Global controls
    void init() {
        // Rendering
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow("Your Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (!window) {
            Logger::logerr("Failed to create window: " + std::string(SDL_GetError()));
            return;
        }

        renderer = Renderer(window);
        SDL_Rect view = renderer.getViewport();
        camera = {player.pos.x - view.w / 2, player.pos.y - view.h / 2, view.w, view.h};
        
        // Components
        assetManager = AssetManager();
        inputManager = InputManager();
        inputManager.setEventHandler([this](GameEvent event) {
            handleGameEvent(event);
        });
        levelManager = LevelManager();
        currentLevel = levelManager.getCurrentLevel();
        player = Player();


        // State
        stateManager = StateManager();
        running = false;
    }

    void run() {
        running = true;
        lastFrameTime = SDL_GetTicks();
        
        while (running) {
            // Timing
            Uint32 currentTime = SDL_GetTicks();
            delta = (currentTime - lastFrameTime) / 1000.0f;
            lastFrameTime = currentTime;

            // Process input
            processInput();

            // Update states
            update(delta);

            // Render updates
            render();
        }
    }

    void quit() {
        SDL_DestroyWindow(window);
        SDL_Quit();
        window = nullptr;
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
    // Rendering
    Renderer renderer;
    SDL_Window* window;
    SDL_Rect camera;

    void resizeWindow(const SDL_WindowEvent& event) {
        SDL_SetWindowSize(window, event.data1, event.data2);
        renderer.update();
        resizeCamera();
    }

    void resizeCamera() {
        SDL_Rect view = renderer.getViewport();
        camera = {
            player.pos.x - view.w / 2,
            player.pos.y - view.h / 2,
            view.w,
            view.h
        };
    }

    void render() {
        

        renderer.clear();
        renderer.draw(tileset, camera);
        renderer.present();
    }

    // Game components
    AssetManager assetManager;
    InputManager inputManager;
    LevelManager levelManager;
    Player player;
    Level currentLevel;

    // State
    StateManager stateManager;
    bool running;
    float delta;
    Uint32 lastFrameTime;

    void processInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            inputManager.handleEvent(event);
        }
    }
    
    void update(float delta) {
        player.update(delta, &inputManager);
        renderer.update();
        resizeCamera();
        currentLevel = levelManager.getCurrentLevel();
    }
};