#pragma once
#include "MenuState.h"
#include "PauseState.h"
#include "PlayState.h"

enum class State {
    Menu,
    Pause,
    Play
};

class GameState {
public:
    GameState();
    ~GameState();

    void changeState(State state);

private:
    State currentState;
};