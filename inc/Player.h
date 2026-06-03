#pragma once
#include "InputManager.h"

struct coords { int x; int y; };

class Player {
public:
    Player() {};
    ~Player() {};

    // Physics
    coords pos;
    coords vel;

    // State
    void update(float delta, const InputManager* inputManager) {
        // Handle player input based on the current input manager state
        if (inputManager->isKeyHeld(Actions::MOVE_LEFT)) {
            // Move left
            pos.x -= static_cast<int>(200 * delta);
        }
        if (inputManager->isKeyHeld(Actions::MOVE_RIGHT)) {
            // Move right
            pos.x += static_cast<int>(200 * delta);
        }
        if (inputManager->isKeyHeld(Actions::JUMP)) {
            // Jump
            pos.y += static_cast<int>(300 * delta);
        }
        if (inputManager->isKeyHeld(Actions::ATTACK)) {
            // Attack
        }

        // TODO: Migrate input manager to player and use keyboard state
        // const Uint8* state = SDL_GetKeyboardState(NULL);

        // if (state[SDL_SCANCODE_A]) {
        //     pos.x -= static_cast<int>(200 * delta); // consolidate into speed var
        // }
    }
};
