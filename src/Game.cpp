#include "Game.h"
#include "GameEvent.h"
#include "InputManager.h"
#include "StateManager.h"

Game::Game() {
    // Rendering
    this->renderer = nullptr;
    this->window = nullptr;
    
    // Components
    this->player = Player();
    
    this->inputManager = InputManager();
    this->inputManager.setEventHandler([this](GameEvent event) {
        this->handleGameEvent(event);
    });

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
    this->renderer = new Renderer(this->window);
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
    if (event == GameEvent::QUIT_REQUESTED) {
        this->running = false;
    }
    else if (event == GameEvent::PAUSE_REQUESTED || event == GameEvent::RESUME_REQUESTED) {
        this->stateManager.togglePause();
    }
    else if (event == GameEvent::DEBUG_REQUESTED) {
        this->stateManager.toggleDebug();
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
}

// Rendering
void Game::render() {
    this->renderer->clear();
    this->renderer->draw();
    this->renderer->present();
}
