#include "Ball.h"

Ball::Ball(int x, int y)
{
    mPosX = x;
    mPosY = y;

    mScore = 0;

    mVelX = -DOT_VEL;
    mVelY = 0;

    mLeftWall = false;
    mRightWall = false;

    mPlayerCount = 0;

    mCollider = new Collider("ball", x, y, BALL_WIDTH, BALL_HEIGHT);
    mBallTexture.loadFromFile("assets\\pongBall_sheet.png");
    mBallTexture.setBlending(SDL_BlendMode::SDL_BLENDMODE_BLEND);
    clipRect = {0, 0, BALL_WIDTH, BALL_HEIGHT};

    SDL_Color textColor = {255, 255, 255};
    mScoreTexture.loadFromText("Score: 0", textColor);
    updateScoreTexture = true;

    createParticles("Main", "assets\\basicParticle.png");
    mPColor = {127, 165, 230, 128};
}

Ball::~Ball()
{
    delete mCollider;
    for(int i=0; i < mNumParticles; ++i){
        delete mParticles[i];
    }
}

void Ball::handleEvents(SDL_Event &e)
{

}

void Ball::move()
{
    mPosX += mVelX;
    mPosY += mVelY;

    const std::string* name = mCollider->checkCollision();

    if(name){
        SDL_Rect* otherCollider = mCollider->getCollider(*name);
        if(otherCollider == nullptr){
            std::cout << "Error getting other collider!" << std::endl;
        }

        mVelX = -mVelX;
        mPosX += mVelX*2;

        int tempY;
        tempY = mPosY - (otherCollider->y + (otherCollider->h / 2));
        if(tempY > 5){
            mVelY += lerp(tempY, 1, 0.93);
        }
        else if(tempY < -5){
            mVelY = -lerp(-tempY, 1, 0.93);
        }

        if(mPosX < otherCollider->x){
            mLeftWall = true;
        }
        else{
            if(mPlayerCount == 1){
                ++mScore;
                updateScoreTexture = true;
            }
            if(mScore % 5 == 0 && mScore > 0){
                mVelX += 2;
            }
        }
    }
    
    if(mPosY < 0 || mPosY + BALL_HEIGHT > SCREEN_HEIGHT){
        mVelY = - mVelY;
        mPosY += mVelY*2;
    }

    if(mPlayerCount == 1){
        if(mPosX + BALL_WIDTH > SCREEN_WIDTH){
            mVelX = -mVelX;
            mPosX += mVelX*2;
        }
        else if(mPosX < 0){
            mLeftWall = true;
        }
    }

    mCollider->setPos(mPosX, mPosY);

    if(updateScoreTexture){
        SDL_Color textColor = {255, 255, 255};
        std::stringstream text;
        text.str();
        text << "Score: " << mScore;
        mScoreTexture.loadFromText(text.str().c_str(), textColor);
        updateScoreTexture = false;
    }

    if(mScore >= 30){
        mPColor = {151, 16, 16, 192};
    }
    else if(mScore >= 20){
        mPColor = {144, 74, 90, 128};
    }
    else if(mScore >= 10){
        mPColor = {155, 90, 230, 128};
    }
}

void Ball::render()
{
    mBallTexture.renderFrames(mPosX, mPosY, &clipRect, 2, 2);

    mScoreTexture.render((SCREEN_WIDTH - mScoreTexture.getWidth()) / 2, 0);
    renderParticles("Main", "assets\\basicParticle.png");
}

void Ball::setPlayerCount(int players)
{
    mPlayerCount = players;
}

bool Ball::hitLeftWall()
{
    if(mLeftWall){
        mLeftWall = false;
        return true;
    }

    return mLeftWall;
}

bool Ball::hitRightWall()
{
    if(mRightWall){
        mRightWall = false;
        return true;
    }

    return mRightWall;
}

int Ball::getPlayerCount()
{
    return mPlayerCount;
}

void Ball::createParticles(const std::string &name, const std::string &path)
{
    for(int i=0; i < mNumParticles; ++i){
        mParticles[i] = new Particle(mPosX, mPosY, *ParticleFactory::getInstance()->getParticleType(name, path));
        mParticles[i]->mPosX = mPosX - 5 +(rand() % 25);
        mParticles[i]->mPosY = mPosY - 5 +(rand() % 25);

        mParticles[i]->setAliveTime((rand() % 80) + 20);
    }
}

void Ball::renderParticles(const std::string &name, const std::string &path)
{
    int followingDirection = -(mVelX / mVelX);

    for(int i=0; i < mNumParticles; ++i){

        if(mParticles[i]->isAlive()){
            mParticles[i]->render(mPColor, 1);
        }
        else{
            delete mParticles[i];
            mParticles[i] = new Particle(mPosX, mPosY, *ParticleFactory::getInstance()->getParticleType(name, path));
            if(mVelX < 0)
                mParticles[i]->mPosX = mPosX + (rand() % 25);
            else if(mVelX > 0)
                mParticles[i]->mPosX = mPosX - (rand() % 25);
            mParticles[i]->mPosY = mPosY - 5 + (rand() % 10) + (mBallTexture.getScaleHeight())/2;
            mParticles[i]->setAliveTime((rand() % 150) + 50);
        }
    }
}