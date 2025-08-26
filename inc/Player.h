#pragma once
#include "InputManager.h"

class Player {
public:
    Player();
    ~Player();

    void handleInput(const InputManager* inputManager);
};
