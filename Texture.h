#ifndef TEXTURE_H
#define TEXTURE_H

#include "Window.h"
#include "Timer.h"
#include <cmath>

class Texture
{
public:
    Texture();
    ~Texture();

    bool loadFromFile(const char* path);
    bool loadFromText(const char* text, SDL_Color& color);

    void render(int x, int y, double scale=1, SDL_Rect* clip=nullptr, double degrees=0.0, SDL_Point* center=nullptr, SDL_RendererFlip flip=SDL_FLIP_NONE);
    void renderFrames(int x, int y, SDL_Rect* clip, int frames, int speed=1, int scale=1, double degrees=0.0, SDL_Point* center=nullptr, SDL_RendererFlip flip=SDL_FLIP_NONE);

    void setColor(uint8_t red, uint8_t green, uint8_t blue);

    void setBlending(SDL_BlendMode blend);

    void setAlpha(uint8_t alpha);

    void free();

    int getWidth();
    int getHeight();

    int getScaleWidth();
    int getScaleHeight();

    bool lockTexture();
    bool unlockTexture();
    void* getPixels();
    int getPitch();
    uint32_t getPixel32(unsigned int x, unsigned int y);
private:
    //our texture
    SDL_Texture* mTexture;

    //width and height of texture
    int mWidth;
    int mHeight;

    int mScaleWidth;
    int mScaleHeight;

    //pixel array and pitch(size of one row of pixels in bytes) of texture
    void* mPixels;
    int mPitch;

    Timer mTimer;
    uint32_t mTime;
    int mFrames;
};

#endif