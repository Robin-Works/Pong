#ifndef PARTICLETYPES_H
#define PARTICLETYPES_H

#include "Texture.h"
#include <string>

class ParticleType
{
public:
    ParticleType(const std::string &type);
    ParticleType(const ParticleType &pType);

    void render(int x, int y, SDL_Color &color, double scale=1, double degrees=0.0);

    void setTexture(const std::string &path);

    std::string getName();
    std::string getPath();

    int getScaleWidth();
    int getScaleHeight();
private:
    std::string mType;
    std::string mPath;
    Texture mTexture;
};

#endif