#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Texture.h"
#include <iostream>

class Statehandler;

class GameState
{
public:
    virtual void handleEvents(Statehandler* sHandler, SDL_Event &e) = 0;

    virtual void doLogic(Statehandler* sHandler) = 0;

    virtual void render(Statehandler* sHandler) = 0;

    virtual void exitState() = 0;
    virtual void enterState() = 0;

    virtual ~GameState() {};
};

#endif