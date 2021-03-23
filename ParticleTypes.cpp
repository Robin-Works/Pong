#include "ParticleTypes.h"

ParticleType::ParticleType(const std::string &type) : mType(type)
{
}

ParticleType::ParticleType(const ParticleType &pType): mType(pType.mType), mPath(pType.mPath)
{
    this->setTexture(pType.mPath);
}

void ParticleType::render(int x, int y, SDL_Color &color, double scale, double degrees)
{
    SDL_Point centerPoint;
    centerPoint.x = mTexture.getScaleWidth() / 2;
    centerPoint.y = mTexture.getScaleHeight() / 2;
    mTexture.setColor(color.r, color.g, color.b);
    mTexture.setAlpha(color.a);
    mTexture.render(x, y, scale, nullptr, degrees, &centerPoint);
}

void ParticleType::setTexture(const std::string &path)
{
    mPath = path;
    if(!mTexture.loadFromFile(mPath.c_str())){
        std::cerr << "Warning: Texture not loaded! Texture path: " << path << std::endl;
    }
    else{
        mTexture.setBlending(SDL_BlendMode::SDL_BLENDMODE_BLEND);
    }
}

std::string ParticleType::getName()
{
    return mType;
}

std::string ParticleType::getPath()
{
    return mPath;
}

int ParticleType::getScaleWidth()
{
    return mTexture.getScaleWidth();
}

int ParticleType::getScaleHeight()
{
    return mTexture.getScaleHeight();
}