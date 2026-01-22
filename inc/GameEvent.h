#pragma once
#include <SDL2/SDL.h>

enum class GameEventType {
    // Game controls
    QUIT_REQUESTED,
    // Window
    WINDOW_RESIZED,
    // Menus
    DEBUG_REQUESTED, // DEV
    PAUSE_REQUESTED,
    RESUME_REQUESTED,
};

class GameEvent {
public:
    GameEvent(SDL_Event sdlEvent, GameEventType type) : sdlEvent(sdlEvent), type(type) {}
    ~GameEvent() {}

    GameEventType type;
    SDL_Event sdlEvent;
};