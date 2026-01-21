#include "AssetManager.h"
#include "Game.h"
#include "GameEvent.h"
#include "InputManager.h"
#include "StateManager.h"
#include "Tilemap.h"

Game::Game() {
    // Rendering
    this->renderer = nullptr;
    this->window = nullptr;
    
    // Components
    this->assetManager = AssetManager();
    this->inputManager = InputManager();
    this->inputManager.setEventHandler([this](GameEvent event) {
        this->handleGameEvent(event);
    });
    // this->levelManager = LevelManager();
    this->player = Player();

    // State
    this->stateManager = StateManager();
    this->running = false;
}
Game::~Game() { 
    this->renderer = nullptr; 
    this->window = nullptr;
}

// Global controls
void Game::init() {
    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow("Your Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!this->window) {
        Logger::logerr("Failed to create window: " + std::string(SDL_GetError()));
        return;
    }
    SDL_Rect view = this->renderer->getViewport();
    this->camera = {player.pos.x - view.w / 2, player.pos.y - view.h / 2, view.w, view.h};
    this->renderer = new Renderer(this->window, view);
}

void Game::run() {
    this->running = true;
    this->lastFrameTime = SDL_GetTicks();
    
    while (this->running) {
        // Timing
        Uint32 currentTime = SDL_GetTicks();
        this->delta = (currentTime - this->lastFrameTime) / 1000.0f;
        this->lastFrameTime = currentTime;

        // Process input
        this->processInput();

        // Update states
        this->update(this->delta);

        // Render updates
        this->render();
    }
}

void Game::quit() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

// Game state
void Game::handleGameEvent(GameEvent& event) {
    if (event.type == GameEventType::QUIT_REQUESTED) {
        this->running = false;
    }
    else if (event.type == GameEventType::PAUSE_REQUESTED || event.type == GameEventType::RESUME_REQUESTED) {
        this->stateManager.togglePause();
    }
    else if (event.type == GameEventType::DEBUG_REQUESTED) {
        this->stateManager.toggleDebug();
    }
    else if (event.type == GameEventType::WINDOW_RESIZED) {
        this->resizeWindow(event.sdlEvent.window);
    }
}

// Process discrete events (quit, single presses, etc.)
void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        this->inputManager.handleEvent(event);
    }
}

void Game::update(float delta) {
    this->player.update(delta, &this->inputManager);
    this->renderer->update();
    this->resizeCamera();
}

void Game::resizeWindow(const SDL_WindowEvent& event) {
    SDL_SetWindowSize(this->window, event.data1, event.data2);

    this->renderer->update();
    this->resizeCamera();
}

void Game::resizeCamera() {
    SDL_Rect view = this->renderer->getViewport();
    this->camera = {
        player.pos.x - view.w / 2,
        player.pos.y - view.h / 2,
        view.w,
        view.h
    };
}

// Rendering
void Game::render() {
    this->renderer->clear();

    Map map;
    this->renderer->draw(map.tileset, this->camera);

    this->renderer->present();
}
