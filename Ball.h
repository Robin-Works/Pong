#ifndef BALL_H
#define BALL_H

#include "Texture.h"
#include "Collider.h"
#include <iostream>
#include <sstream>
#include "Particle.h"

class Ball
{
public:
    static const int BALL_WIDTH = 16;
    static const int BALL_HEIGHT = 16;

    static const int DOT_VEL = 5;

    Ball(int x, int y);
    ~Ball();

    void render();

    void handleEvents(SDL_Event &e);

    void move();

    void setPlayerCount(int players);
    int getPlayerCount();

    bool hitLeftWall();
    bool hitRightWall();
private:
    int mPosX;
    int mPosY;

    int mVelX;
    int mVelY;

    bool mLeftWall, mRightWall;
    int mPlayerCount;

    Texture mBallTexture;
    SDL_Rect clipRect;

    Collider *mCollider;

    Texture mScoreTexture;
    int mScore;
    bool updateScoreTexture;

    static const int mNumParticles = 20;

    Particle* mParticles[mNumParticles];

    SDL_Color mPColor;

    void createParticles(const std::string &name, const std::string &path);
    void renderParticles(const std::string &name, const std::string &path);
};

#endif