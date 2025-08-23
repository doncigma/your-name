#include "InputManager.h"

InputManager::InputManager() {
    mappings[SDL_SCANCODE_F1] = Actions::DEBUG_TOGGLE; // DEV
    mappings[SDL_SCANCODE_ESCAPE] = Actions::QUIT; // DEV
    mappings[SDL_SCANCODE_P] = Actions::PAUSE; // will be ESC
    mappings[SDL_SCANCODE_A] = Actions::MOVE_LEFT;
    mappings[SDL_SCANCODE_LEFT] = Actions::MOVE_LEFT;
    mappings[SDL_SCANCODE_D] = Actions::MOVE_RIGHT;
    mappings[SDL_SCANCODE_RIGHT] = Actions::MOVE_RIGHT;
    mappings[SDL_SCANCODE_SPACE] = Actions::JUMP;
    mappings[SDL_SCANCODE_UP] = Actions::JUMP;
    mappings[SDL_SCANCODE_K] = Actions::ATTACK; // will be right click
}
InputManager::~InputManager() {}

void InputManager::processInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        auto it = mappings.find(event.key.keysym.scancode);
        if (it != mappings.end()) return;

        // Handle the action
        Actions action = it->second;
        if (action == Actions::QUIT) {
            // Example: set a flag to quit the game
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }
        else if (action == Actions::PAUSE) {
            // toggle pause state
        }
        else if (action == Actions::MOVE_LEFT) {
            // move player left
        }
        else if (action == Actions::MOVE_RIGHT) {
            // move player right
        }
        else if (action == Actions::JUMP) {
            // make player jump
        }
        else if (action == Actions::ATTACK) {
            // make player attack
        }
        else if (action == Actions::DEBUG_TOGGLE) {
            // toggle debug mode
        }
    }
    
}