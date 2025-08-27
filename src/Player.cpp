#include "Player.h"
#include "InputManager.h"

Player::Player() {}
Player::~Player() {}

void Player::update(float delta, const InputManager* inputManager) {
    // Handle player input based on the current input manager state
    if (inputManager->isKeyHeld(Actions::MOVE_LEFT)) {
        // Move left
    }
    if (inputManager->isKeyHeld(Actions::MOVE_RIGHT)) {
        // Move right
    }
    if (inputManager->isKeyHeld(Actions::JUMP)) {
        // Jump
    }
    if (inputManager->isKeyHeld(Actions::ATTACK)) {
        // Attack
    }
}
