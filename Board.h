#ifndef BOARD_H
#define BOARD_H
#include "Collider.h"
#include "Texture.h"
#include <iostream>
#include <SDL.h>

class Board
{
public:
    static const int BOARD_VEL = 5;
    static const int BOARD_WIDTH = 16;
    static const int BOARD_HEIGHT = 128;

    Board(std::string name, int x, int y);
    ~Board();

    void handleEvents(SDL_Event &e);

    void move();

    void render();

private:
    Texture mBoardTexture;

    int mPosX;
    int mPosY;

    int mVelY;

    std::string mName;

    Collider *mCollider;
};

#endif