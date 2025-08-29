#include "GameEvent.h"
#include "InputManager.h"
#include "Logger.h"

void InputManager::handleEvent(SDL_Event& event) {
    auto type = event.type;
    if (type == SDL_QUIT) {
        // Handle quit event
        this->heldKeys[Actions::QUIT] = true;
        this->fireEvent(GameEvent(event, GameEventType::QUIT_REQUESTED));
    }
    else if (type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
        this->fireEvent(GameEvent(event, GameEventType::WINDOW_RESIZED));
    }
    else if (type == SDL_KEYDOWN) {
        auto it = mappings.find(event.key.keysym.scancode);
        if (it == mappings.end()) return;

        // Handle the action
        Actions action = it->second;
        Logger::log("InputManager::handleEvent(): Action triggered: " + std::to_string(static_cast<int>(action))); // DEBUG
        if (action == Actions::DEBUG_TOGGLE) {
            this->toggleKeyHeld(action);
            this->fireEvent(GameEvent(event, GameEventType::DEBUG_REQUESTED));
        }
        else if (action == Actions::QUIT) {
            this->fireEvent(GameEvent(event, GameEventType::QUIT_REQUESTED));
        }
        else if (action == Actions::PAUSE) {
            this->toggleKeyHeld(action);
            this->fireEvent(GameEvent(event, GameEventType::PAUSE_REQUESTED));
        }
        else if (action == Actions::MOVE_LEFT) {
            this->toggleKeyHeld(action);
        }
        else if (action == Actions::MOVE_RIGHT) {
            this->toggleKeyHeld(action);
        }
        else if (action == Actions::JUMP) {
            this->toggleKeyHeld(action);
        }
        else if (action == Actions::ATTACK) {
            this->toggleKeyHeld(action);
        }
    }
    else if (type == SDL_KEYUP) {
        auto it = mappings.find(event.key.keysym.scancode);
        if (it == mappings.end()) return;

        // Handle the action
        Actions action = it->second;
        this->toggleKeyHeld(action);
    }
    else if (type == SDL_MOUSEBUTTONDOWN) {
        Uint8 button = event.button.button;
        if (button == SDL_BUTTON_LEFT) {
            // this->fireEvent(GameEvent(event, GameEventType::ATTACK));
        }
        else if (button == SDL_BUTTON_RIGHT) {
            // this->fireEvent(GameEvent(event, GameEventType::MOUSE_RIGHT_CLICK));
        }
    }
}

inline bool InputManager::isKeyHeld(Actions action) const {
    auto it = heldKeys.find(action);
    return (it == heldKeys.end() ? false : it->second);
}

inline void InputManager::fireEvent(GameEvent event) {
    this->eventHandler
        ? this->eventHandler(event)
        : Logger::logerr("InputManager::fire(): No event handler set");
}
