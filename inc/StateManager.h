#pragma once

enum class GameState {
    START_MENU,
    PAUSE_MENU,
    PLAY
};

class StateManager {
public:
    StateManager() { this->currentState = GameState::START_MENU; };
    ~StateManager() {};

    inline GameState getCurrentState() const { return this->currentState; };
    inline void changeState(GameState state) { this->currentState = state; };
    
    inline void togglePause() {
        this->currentState = (this->currentState == GameState::PAUSE_MENU) ? GameState::PLAY : GameState::PAUSE_MENU;
    };

private:
    GameState currentState;
};