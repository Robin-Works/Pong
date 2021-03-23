#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <SDL.h>

#include "GameState.h"

class Statehandler
{
public:
    Statehandler();

    void handleEvents(SDL_Event &e);

    void doLogic();

    void render();

    void setState(GameState* newState);

    void exitState(GameState* oldState);
    void enterState(GameState* newState);
private:
    // friend class GameState;
    // void changeState(GameState* state);
    GameState* mState;
};

#endif