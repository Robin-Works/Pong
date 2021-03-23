#include "Button.h"

Button::Button()
{
    mInside = false;
    mPressed = false;
    mUnpressed = false;
    mFullClicked = false;

    mPosX = 0;
    mPosY = 0;
}

void Button::handleEvents(SDL_Event &e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION){
        int mouseX, mouseY;

        SDL_GetMouseState(&mouseX, &mouseY);
        int buttonX = mPosX;
        int buttonY = mPosY;

        int windowW, windowH;
        SDL_GetWindowSize(Window::getInstance()->getWindow(), &windowW, &windowH);
        int renderW, renderH;
        SDL_RenderGetLogicalSize(Window::getInstance()->getRenderer(), &renderW, &renderH);

        double offSetX = 0;
        double offSetY = 0;
        if(!Window::getInstance()->isFullscreen()){
            if((static_cast<double>(windowW) / windowH) > (4.0 / 3.0)){
                offSetX = windowW;
                windowW = (4.0/3.0)*windowH;

                offSetX = ((offSetX - windowW) / 2) / windowW * renderW;
            }
            else if((static_cast<double>(windowW) / windowH) < (4.0 / 3.0)){
                offSetY = windowH;
                windowH = (3.0/4.0)*windowW;

                offSetY = ((offSetY - windowH) / 2) / windowH * renderH;
            }
        }

        double mousefX = static_cast<double>(mouseX) / static_cast<double>(windowW) * static_cast<double>(renderW);
        double mousefY = static_cast<double>(mouseY) / static_cast<double>(windowH) * static_cast<double>(renderH);
        if(!Window::getInstance()->isFullscreen()){
            mousefX -= offSetX;
            mousefY -= offSetY;
        }

        mInside = true;

        if(static_cast<int>(mousefX) < buttonX){
            mInside = false;
        }
        else if(static_cast<int>(mousefX) > buttonX + mWidth){
            mInside = false;
        }
        else if(static_cast<int>(mousefY) < buttonY){
            mInside = false;
        }
        else if(static_cast<int>(mousefY) > buttonY + mHeight){
            mInside = false;
        }

        if(mInside){
            switch(e.type){
                case SDL_MOUSEBUTTONDOWN:
                mPressed = true;
                mUnpressed = false;
                break;

                case SDL_MOUSEBUTTONUP:
                mUnpressed = true;
                if(mPressed){
                    mFullClicked = true;
                }
                mPressed = false;
                break;
            }
        }
        else if(e.type == SDL_MOUSEBUTTONUP){
            mUnpressed = true;
            mPressed = false;
        }
    }
}

void Button::render(int x, int y)
{
    if(mInside){
        mButtonTexture.setColor(128, 128, 128);
        if(mPressed){
            mButtonTexture.setColor(64, 64, 64);
        }
    }
    else{
        mButtonTexture.setColor(255, 255, 255);
    }

    mPosX = x;
    mPosY = y;
    mButtonTexture.render(mPosX, mPosY);
}

void Button::loadTexture(const std::string &path)
{
    mButtonTexture.loadFromFile(path.c_str());

    mWidth = mButtonTexture.getWidth();
    mHeight = mButtonTexture.getHeight();
    mButtonTexture.setBlending(SDL_BlendMode::SDL_BLENDMODE_BLEND);
}

bool Button::isInside()
{
    return mInside;
}

bool Button::isPressed()
{
    return mPressed;
}

bool Button::isUnpressed()
{
    return mUnpressed;
}

bool Button::clicked()
{
    if(mFullClicked){
        mFullClicked = false;
        mInside = false;
        return true;
    }
    return false;
}

int Button::getWidth()
{
    return mWidth;
}

int Button::getHeight()
{
    return mHeight;
}