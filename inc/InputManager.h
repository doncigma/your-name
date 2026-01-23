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
    inline bool isKeyHeld(Actions action) const {
        auto it = heldKeys.find(action);
        return (it == heldKeys.end() ? false : it->second);
    }
    
    // Event handling
    void handleEvent(SDL_Event& event) {
        auto type = event.type;
        if (type == SDL_QUIT) {
            // Handle quit event
            heldKeys[Actions::QUIT] = true;
            fireEvent(GameEvent(event, GameEventType::QUIT_REQUESTED));
        }
        else if (type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            fireEvent(GameEvent(event, GameEventType::WINDOW_RESIZED));
        }
        else if (type == SDL_KEYDOWN) {
            auto it = mappings.find(event.key.keysym.scancode);
            if (it == mappings.end()) return;

            // Handle the action
            Actions action = it->second;
            // Logger::log("InputManager::handleEvent(): Action triggered: " + std::to_string(static_cast<int>(action))); // DEBUG
            if (action == Actions::DEBUG_TOGGLE) {
                toggleKeyHeld(action);
                fireEvent(GameEvent(event, GameEventType::DEBUG_REQUESTED));
            }
            else if (action == Actions::QUIT) {
                fireEvent(GameEvent(event, GameEventType::QUIT_REQUESTED));
            }
            else if (action == Actions::PAUSE) {
                toggleKeyHeld(action);
                fireEvent(GameEvent(event, GameEventType::PAUSE_REQUESTED));
            }
            else if (action == Actions::MOVE_LEFT) {
                toggleKeyHeld(action);
            }
            else if (action == Actions::MOVE_RIGHT) {
                toggleKeyHeld(action);
            }
            else if (action == Actions::JUMP) {
                toggleKeyHeld(action);
            }
            else if (action == Actions::ATTACK) {
                toggleKeyHeld(action);
            }
        }
        else if (type == SDL_KEYUP) {
            auto it = mappings.find(event.key.keysym.scancode);
            if (it == mappings.end()) return;

            // Handle the action
            Actions action = it->second;
            toggleKeyHeld(action);
        }
        else if (type == SDL_MOUSEBUTTONDOWN) {
            Uint8 button = event.button.button;
            if (button == SDL_BUTTON_LEFT) {
                // fireEvent(GameEvent(event, GameEventType::ATTACK));
            }
            else if (button == SDL_BUTTON_RIGHT) {
                // fireEvent(GameEvent(event, GameEventType::MOUSE_RIGHT_CLICK));
            }
        }
    }

    inline void setEventHandler(std::function<void(GameEvent)> handler) { eventHandler = handler; }
    
private:
    // Key state
    std::unordered_map<Actions, bool> heldKeys;
    std::function<void(GameEvent)> eventHandler;

    inline bool toggleKeyHeld(Actions action) { return (heldKeys[action] = !heldKeys[action]); }

    // Event handling
    inline void fireEvent(GameEvent event) {
        eventHandler
        ? eventHandler(event)
        : Logger::logerr("InputManager::fire(): No event handler set");
    }
};
