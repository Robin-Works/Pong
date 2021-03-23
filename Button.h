#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"

class Button
{
public:
    Button();

    void render(int x, int y);

    void handleEvents(SDL_Event &e);

    void loadTexture(const std::string &path);

    bool isInside();
    bool isPressed();
    bool isUnpressed();
    bool clicked();

    int getWidth();
    int getHeight();
private:
    Texture mButtonTexture;
    int mWidth;
    int mHeight;

    int mPosX;
    int mPosY;

    bool mInside;
    bool mPressed;
    bool mUnpressed;
    bool mFullClicked;
};

#endif