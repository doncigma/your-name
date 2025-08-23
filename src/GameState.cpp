#include "GameState.h"

GameState::GameState() {
    this->currentState = State::Play;
}
GameState::~GameState() {}


void GameState::changeState(State state) {
    this->currentState = state;
}