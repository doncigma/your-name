#include "Game.h"
#include "StateManager.h"

Game::Game() {
    // Rendering
    this->renderer = nullptr;
    this->window = nullptr;
    
    // Components
    this->player = Player();
    this->inputManager = InputManager();
    
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
    SDL_Event event;
    
    while (this->running) {
        // Process discrete events (quit, single presses, etc.)
        while (SDL_PollEvent(&event)) {
            this->inputManager.handleEvent(event);
        }

        // Handle continuous input states (movement, key holds, etc.)
        this->player.handleInput(&this->inputManager);

        this->update();
        this->render();
    }
}

void Game::quit() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

// Rendering
void Game::update() {
    // Update game state
}

void Game::render() {
    this->renderer->clear();
    this->renderer->present();
}
