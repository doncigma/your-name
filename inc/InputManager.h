#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>

enum class Actions {
    DEBUG_TOGGLE, // DEV
    QUIT, // DEV
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

    std::unordered_map<SDL_Scancode, Actions> mappings;

    void processInput(SDL_Event& event);
};
