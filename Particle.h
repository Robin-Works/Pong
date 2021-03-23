#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleFactory.h"
#include "Timer.h"

class Particle
{
public:
    Particle(int x, int y, ParticleType &type);
    ~Particle();

    void render(SDL_Color &color, double scale=1.0, double degrees=0.0);

    bool isAlive();

    void setAliveTime(int time);

    int mPosX;
    int mPosY;

    int mVelX;
    int mVelY;

    int getScaleWidth();
    int getScaleHeight();
private:
    Timer mTimer;

    int mAlive;

    ParticleType *mType;
};

#endif