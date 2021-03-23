#include "Texture.h"

Texture::Texture()
{
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;

    mScaleWidth = 0;
    mScaleHeight = 0;

    mTime = 0;
    mFrames = 0;
    mTimer.start();
}

Texture::~Texture()
{
    free();
}

//load texture from relative path
bool Texture::loadFromFile(const char* path)
{
    free();

    SDL_Texture* blankTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if(!loadedSurface){
        std::cout << "Error loading surface! Error: " << IMG_GetError() << std::endl;
    }
    else{
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
        if(!formattedSurface){
            std::cout << "Error converting surface to display format!" << std::endl;
        }
        else{
            blankTexture = SDL_CreateTexture(Window::getInstance()->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
            if(!blankTexture){
                std::cout << "Error creating blank texture! Error: " << SDL_GetError() << std::endl;
            }
            else{
                SDL_LockTexture(blankTexture, nullptr, &mPixels, &mPitch);

                memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

                SDL_UnlockTexture(blankTexture);
                mPixels = nullptr;
                mWidth = formattedSurface->w;
                mHeight = formattedSurface->h;
            }

            SDL_FreeSurface(formattedSurface);
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = blankTexture;
    return mTexture != nullptr;
}

//load texture from input text and color
bool Texture::loadFromText(const char* text, SDL_Color& color)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, color);
    if(!textSurface){
        std::cout << "Error creating text surface! Error: " << TTF_GetError() << std::endl;
    }
    else{
        mTexture = SDL_CreateTextureFromSurface(Window::getInstance()->getRenderer(), textSurface);
        if(!mTexture){
            std::cout << "Error creating texture from surface! Error: " << SDL_GetError() << std::endl;
        }
        else{
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return mTexture != nullptr;
}

//render text at x and y coordinates
//clip defines the clip from the image you want to render from
//degrees defines the angle at which you want to rotate the texture
//center defines the center of the texture for which you rotate and flip around
//flip defines the type of reflection you want on the textur
void Texture::render(int x, int y, double scale, SDL_Rect* clip, double degrees, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if(clip){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    if(scale > 1){
        mScaleWidth = renderQuad.w * scale;
        mScaleHeight = renderQuad.h * scale;

        renderQuad.w = mScaleWidth;
        renderQuad.h = mScaleHeight;
    }
    else{
        mScaleWidth = mWidth;
        mScaleHeight = mHeight;
    }

    SDL_RenderCopyEx(Window::getInstance()->getRenderer(), mTexture, clip, &renderQuad, degrees, center, flip);
}

//Have to specify a clip in order to animate
//Frames specify the amount frames of animation
//speed specifies how fast the animation plays: 1 is equivalent to 1/10 a second
void Texture::renderFrames(int x, int y, SDL_Rect* clip, int frames, int speed, int scale, double degrees, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, clip->w, clip->h};

    if(mTimer.getTicks() >= (speed*100)){
        ++mFrames;

        if((mFrames) >= frames){
            mFrames = 0;
            clip->x = 0;
            clip->y = 0;
        }
        mTimer.stop();
        mTimer.start();
    }


    clip->x = clip->w * mFrames;
    if(clip->x >= mWidth){
        clip->x = 0;
        mFrames = 0;
        clip->y += clip->h;
    }

    if(scale > 1){
        mScaleWidth = renderQuad.w * scale;
        mScaleHeight = renderQuad.h * scale;

        renderQuad.w = mScaleWidth;
        renderQuad.h = mScaleHeight;
    }
    else{
        mScaleWidth = mWidth;
        mScaleHeight = mHeight;
    }

    SDL_RenderCopyEx(Window::getInstance()->getRenderer(), mTexture, clip, &renderQuad, degrees, center, flip);
}

//color modulate background color
void Texture::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

//set blend mode
void Texture::setBlending(SDL_BlendMode blend)
{
    SDL_SetTextureBlendMode(mTexture, blend);
}

//alpha modulate the texture
void Texture::setAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

//destroy texture if one exists
void Texture::free()
{
    if(mTexture){
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;

        mWidth = 0;
        mHeight = 0;
    }
}

int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}

int Texture::getScaleWidth()
{
    return mScaleWidth;
}

int Texture::getScaleHeight()
{
    return mScaleHeight;
}

//lock texture for pixel access
//returns true if successfull, false if already locked or unable to lock
bool Texture::lockTexture()
{
    bool success(true);

    if(mPixels){
        std::cout << "Texture already locked!" << std::endl;
        success = false;
    }
    else{
        if(SDL_LockTexture(mTexture, nullptr, &mPixels, &mPitch) != 0){
            std::cout << "Unable to lock texture!" << std::endl;
            success = false;
        }
    }

    return success;
}

//unlock texture to update pixels
//return true if successfull, false if already unlocked
bool Texture::unlockTexture()
{
    bool success(true);

    if(!mPixels){
        std::cout << "Texture already locked!" << std::endl;
        success = false;
    }
    else{
        SDL_UnlockTexture(mTexture);
        mPixels = nullptr;
        mPitch = 0;
    }

    return success;
}

void* Texture::getPixels()
{
    return mPixels;
}

int Texture::getPitch()
{
    return mPitch;
}