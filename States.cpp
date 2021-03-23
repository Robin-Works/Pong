#include "States.h"
StartState* StartState::mInstance = nullptr;

    ///////////////////////////////
   //                           //
  //        START STATE        //
 //                           //
///////////////////////////////

StartState::StartState()
{
    mPlayGame = false;
    mPressed = false;
    mUnpressed = false;

    SDL_Color textColor = {255, 255, 255};

    mTitleText.loadFromFile("assets\\title.png");
    mStartButton.loadTexture("assets\\play.png");
    mBg.loadFromFile("assets\\bg.png");
    mQuit.loadTexture("assets\\quit.png");

    mTitleText.setBlending(SDL_BlendMode::SDL_BLENDMODE_BLEND);
}

//returns the instance of our start state
GameState* StartState::instance()
{
    return mInstance? mInstance : (mInstance = new StartState);
}

void StartState::handleEvents(Statehandler* handler, SDL_Event &e)
{
    mStartButton.handleEvents(e);

    mQuit.handleEvents(e);
}

void StartState::doLogic(Statehandler* handler)
{
    if(mStartButton.clicked()){
        handler->exitState(StartState::instance());
        handler->setState(MainState::instance());
        handler->enterState(MainState::instance());
    }
    else if(mQuit.clicked()){
        Window::getInstance()->mQuit = true;
    }
}

void StartState::render(Statehandler* handler)
{
    SDL_ShowCursor(1);
    SDL_RenderSetLogicalSize(Window::getInstance()->getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
    for(int i=0; i < SCREEN_HEIGHT; i+=mBg.getHeight()){
        for(int j=0; j < SCREEN_WIDTH; j+=mBg.getWidth()){
            mBg.render(j, i);
        }
    }

    mTitleText.render((SCREEN_WIDTH - mTitleText.getWidth()) / 2, mTitleText.getHeight() / 4);

    mStartButton.render((SCREEN_WIDTH - mStartButton.getWidth()) / 2, (SCREEN_HEIGHT - mStartButton.getHeight()) / 2);

    mQuit.render((SCREEN_WIDTH - mQuit.getWidth()) / 2, ((SCREEN_HEIGHT - mStartButton.getHeight()) / 2) + mQuit.getHeight());
}

void StartState::exitState()
{
    mPressed = false;
    mUnpressed = false;
    mInside = false;
}

void StartState::enterState()
{

}

    ///////////////////////////////
   //                           //
  //        MAIN STATE         //
 //                           //
///////////////////////////////

MainState* MainState::mInstance = nullptr;

MainState::MainState()
{
    mRepeatPrompt.loadTexture("assets\\playAgain.png");
    mBg.loadFromFile("assets\\bg.png");
}

MainState::~MainState()
{
    delete mBall;
    delete mBoard;
}

GameState* MainState::instance()
{
    return mInstance? mInstance : (mInstance = new MainState);
}

void MainState::handleEvents(Statehandler* handler, SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_ESCAPE){
            handler->exitState(MainState::instance());
            handler->setState(StartState::instance());
            handler->enterState(StartState::instance());
        }
    }

    if(mRenderRepeat){
        mRepeatPrompt.handleEvents(e);
    }
    else{
        mBoard->handleEvents(e);
    }
}

void MainState::doLogic(Statehandler* handler)
{
    if(!mRenderRepeat){
        mBoard->move();
        mBall->move();
    }

    if(mBall->getPlayerCount() == 1){
        if(mBall->hitLeftWall() || mRenderRepeat){
            mRenderRepeat = true;

            
            if(mRepeatPrompt.clicked()){
                exitState();
                enterState();
            }
        }
    }
}

void MainState::render(Statehandler* handler)
{
    SDL_RenderSetLogicalSize(Window::getInstance()->getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
    for(int i=0; i < SCREEN_HEIGHT; i+=mBg.getHeight()){
        for(int j=0; j < SCREEN_WIDTH; j+=mBg.getWidth()){
            mBg.render(j, i);
        }
    }

    if(mRenderRepeat){
        SDL_ShowCursor(1);
        mRepeatPrompt.render((SCREEN_WIDTH - mRepeatPrompt.getWidth()) / 2, (SCREEN_HEIGHT - mRepeatPrompt.getHeight()) / 2);
    }
    else{
        SDL_ShowCursor(0);
        mBall->render();
        mBoard->render();
    }
}

void MainState::exitState()
{
    delete mBall;
    delete mBoard;

    mInside = false;
    mPressed = false;
    mUnpressed = false;

    mRenderRepeat = false;
}

void MainState::enterState()
{
    if(!mInstance){
        mInstance = new MainState;
    }
    else{
        mBall = new Ball((SCREEN_WIDTH - Ball::BALL_WIDTH)/ 2, (SCREEN_HEIGHT - Ball::BALL_HEIGHT)/ 2);
        mBoard = new Board("board1", 16, (SCREEN_HEIGHT - Board::BOARD_HEIGHT) / 2);

        mBall->setPlayerCount(1);
        mRenderRepeat = false;
        mPressed = false;
        mUnpressed = false;
        mInside = false;
    }
}