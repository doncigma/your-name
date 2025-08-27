#pragma once
#include "InputManager.h"

class Player {
public:
    Player();
    ~Player();

    void update(float delta, const InputManager* inputManager);
};
