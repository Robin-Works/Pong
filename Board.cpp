#include "Board.h"

Board::Board(std::string name, int x, int y)
{
    mPosX = x;
    mPosY = y;

    mName = name;

    mVelY = 0;
    mBoardTexture.loadFromFile("assets\\pongBoard.png");
    mBoardTexture.setBlending(SDL_BlendMode::SDL_BLENDMODE_BLEND);
    mCollider = new Collider(mName, mPosX, mPosY, BOARD_WIDTH, BOARD_HEIGHT);
}

Board::~Board()
{
    delete mCollider;
}

void Board::handleEvents(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: mVelY -= BOARD_VEL; break;
            case SDLK_DOWN: mVelY += BOARD_VEL; break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: mVelY += BOARD_VEL; break;
            case SDLK_DOWN: mVelY -= BOARD_VEL; break;
        }
    }
}

void Board::move()
{
    mPosY += mVelY;

    if((mPosY < 0) || (mPosY + BOARD_HEIGHT > SCREEN_HEIGHT)){
        mPosY -= mVelY;
    }

    mCollider->setPos(mPosX, mPosY);
}

void Board::render()
{
    mCollider->setDimensions(mBoardTexture.getWidth(), mBoardTexture.getHeight());

    mBoardTexture.render(mPosX, mPosY);
}