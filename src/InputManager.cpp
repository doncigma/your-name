#include "InputManager.h"
#include "Logger.h"

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

void InputManager::handleEvent(SDL_Event& event) {
    auto type = event.type;
    if (type == SDL_QUIT) {
        // Handle quit event
        this->heldKeys[Actions::QUIT] = true;
        this->fireEvent(GameEvent::QUIT_REQUESTED);
    }
    else if (type == SDL_KEYDOWN) {
        auto it = mappings.find(event.key.keysym.scancode);
        if (it == mappings.end()) return;

        // Handle the action
        Actions action = it->second;
        if (action == Actions::DEBUG_TOGGLE) {
            if (this->heldKeys[action])
                this->fireEvent(GameEvent::DEBUG_OFF);
            else this->fireEvent(GameEvent::DEBUG_ON);
        }
        else if (action == Actions::QUIT) {
            this->fireEvent(GameEvent::QUIT_REQUESTED);
        }
        else if (action == Actions::PAUSE) {
            this->fireEvent(GameEvent::PAUSE_REQUESTED);
        }
        else if (action == Actions::MOVE_LEFT) {
            // update key state
        }
        else if (action == Actions::MOVE_RIGHT) {
            // update key state
        }
        else if (action == Actions::JUMP) {
            // update key state
        }
        else if (action == Actions::ATTACK) {
            // update key state
        }
    }
    else if (type == SDL_MOUSEBUTTONDOWN) {
        Uint8 button = event.button.button;
        if (button == SDL_BUTTON_LEFT) {
            // Handle left mouse button click
        }
        else if (button == SDL_BUTTON_RIGHT) {
            // Handle right mouse button click
        }
    }
}

bool InputManager::isKeyHeld(Actions action) const {
    auto it = heldKeys.find(action);
    if (it == heldKeys.end()) return false;
    return it->second;
}
