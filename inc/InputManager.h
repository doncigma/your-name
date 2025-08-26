#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>
#include "Game.h"

enum class Actions {
    DEBUG_TOGGLE,
    QUIT,
    PAUSE,
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    ATTACK
};

class InputManager {
public:
    InputManager();
    ~InputManager();
    
    // Actions
    /// @brief Key mappings from `SDL_SCANCODES` to `Actions`
    std::unordered_map<SDL_Scancode, Actions> mappings;

    // Key state
    bool isKeyHeld(Actions action) const;

    // Event handling
    void handleEvent(SDL_Event& event);
    inline void setEventHandler(std::function<void(GameEvent& event)> handler) { this->eventHandler = handler; }
    
private:
    // Key state
    std::unordered_map<Actions, bool> heldKeys;
    void update();

    // Event handling
    std::function<void(GameEvent& event)> eventHandler;
    inline void fireEvent(GameEvent event) {
        eventHandler ? eventHandler(event) : Logger::logerr("InputManager::fire(): No event handler set");
    }
};
