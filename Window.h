#ifndef WINDOW_H
#define WINDOW_H

#include "Global.h"
#include <iostream>

class Window
{
public:

    bool init();

    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();

    void handleEvent(SDL_Event &e);

    void free();

    static Window* getInstance();

    int getWidth();
    int getHeight();

    bool hasMouseFocus();
    bool hadKeyboardFocus();
    bool isMinimized();
    bool isShown();

    bool isFullscreen();

    int SCALEX;
    int SCALEY;
    bool mQuit;
private:
    Window();
    ~Window();

    //our renderer and window
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    //width, height, and the displayID
    int mWidth;
    int mHeight;
    int mWindowDisplayID;

    //keeps track of mouse focus, keyboard focus, fullscreen, minimization, and the window being shown
    bool mMouseFocus;
    bool mKeyboardFocus;
    bool mFullScreen;
    bool mMinimized;
    bool mShown;

    //our singular window instance
    static Window* mInstance;

    int prevScaleX;
    int prevScaleY;
};

#endif