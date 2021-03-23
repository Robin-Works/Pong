#include "Statehandler.h"
#include "States.h"

Statehandler::Statehandler()
{
    mState = StartState::instance();
}

void Statehandler::handleEvents(SDL_Event &e)
{
    mState->handleEvents(this, e);
}

void Statehandler::doLogic()
{
    mState->doLogic(this);
}

void Statehandler::render()
{
    mState->render(this);
}

void Statehandler::setState(GameState* newState)
{
    mState = newState;
}

void Statehandler::exitState(GameState* oldState)
{
    oldState->exitState();
}

void Statehandler::enterState(GameState* newState)
{
    newState->enterState();
}