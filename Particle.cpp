#include "Particle.h"

Particle::Particle(int x, int y, ParticleType &type)
{
    mPosX = x;
    mPosY = y;

    mType = new ParticleType(type);
    mTimer.start();
}

Particle::~Particle()
{
    delete mType;
}

void Particle::setAliveTime(int time)
{
    mAlive = time;
}

//alive time is in milliseconds
bool Particle::isAlive()
{
    if(mTimer.getTicks() <= mAlive){
        return true;
    }
    mTimer.stop();
    mTimer.start();
    return false;
}

void Particle::render(SDL_Color &color, double scale, double degrees)
{
    mType->render(mPosX, mPosY, color, scale, degrees);
}

int Particle::getScaleWidth()
{
    return mType->getScaleWidth();
}

int Particle::getScaleHeight()
{
    return mType->getScaleHeight();
}
