#pragma once
#include <functional>
#include <SDL2/SDL.h>
#include <unordered_map>
#include "GameEvent.h"
#include "Logger.h"

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
    InputManager() {};
    InputManager(std::function<void(GameEvent)> handler) : eventHandler(handler) {};
    ~InputManager() {};

    // Actions
    /// @brief Key mappings from `SDL_SCANCODES` to `Actions`
    static const inline std::unordered_map<SDL_Scancode, Actions> mappings = {
        {SDL_SCANCODE_ESCAPE, Actions::QUIT},
        {SDL_SCANCODE_P, Actions::PAUSE},
        {SDL_SCANCODE_F1, Actions::DEBUG_TOGGLE},
        {SDL_SCANCODE_A, Actions::MOVE_LEFT},
        {SDL_SCANCODE_D, Actions::MOVE_RIGHT},
        {SDL_SCANCODE_SPACE, Actions::JUMP},
        {SDL_SCANCODE_K, Actions::ATTACK}
    };

    // Key state
    inline bool isKeyHeld(Actions action) const;
    
    // Event handling
    void handleEvent(SDL_Event& event);
    inline void setEventHandler(std::function<void(GameEvent)> handler) { this->eventHandler = handler; }
    
private:
    // Key state
    std::unordered_map<Actions, bool> heldKeys;
    inline bool toggleKeyHeld(Actions action) { return (this->heldKeys[action] = !this->heldKeys[action]); }

    // Event handling
    std::function<void(GameEvent)> eventHandler;
    inline void fireEvent(GameEvent event);
};
