#pragma once
#include "InputManager.h"

struct coords { int x; int y; };

class Player {
public:
    Player();
    ~Player();

    // Physics
    coords pos;
    coords vel;

    // State
    void update(float delta, const InputManager* inputManager);
};
