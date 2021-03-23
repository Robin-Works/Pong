#ifndef STATES_H
#define STATES_H

#include "Statehandler.h"
#include "Ball.h"
#include "Board.h"
#include "Button.h"
#include <sstream>

    ///////////////////////////////
   //                           //
  //        START STATE        //
 //                           //
///////////////////////////////

class StartState : public GameState
{
public:
    virtual void handleEvents(Statehandler* handler, SDL_Event &e) override;

    virtual void doLogic(Statehandler* handler) override;

    virtual void render(Statehandler* handler) override;

    virtual void exitState() override;
    virtual void enterState() override;

    static GameState* instance();
private:
    StartState();
    Texture mTitleText;
    Button mStartButton;
    Texture mBg;
    Button mQuit;

    bool mPlayGame;

    bool mPressed, mUnpressed;
    bool mInside;

    static StartState* mInstance;
};

    ///////////////////////////////
   //                           //
  //        MAIN STATE         //
 //                           //
///////////////////////////////

class MainState : public GameState
{
public:
    static GameState* instance();
    ~MainState();

    virtual void handleEvents(Statehandler* handler, SDL_Event &e) override;

    virtual void doLogic(Statehandler* handler) override;

    virtual void render(Statehandler* handler) override;

    virtual void exitState() override;
    virtual void enterState() override;
private:
    MainState();
    
    Ball *mBall;
    Board *mBoard;
    static MainState* mInstance;

    Button mRepeatPrompt;
    Texture mBg;
    bool mRenderRepeat;
    bool mPressed, mUnpressed;
    bool mInside;
};

#endif