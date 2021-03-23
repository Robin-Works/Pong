#include "Window.h"

//Declare our singular instance
Window* Window::mInstance = nullptr;

Window::Window()
{
    mWindow = nullptr;
    mRenderer = nullptr;
    mShown = false;
    mMinimized = false;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mWidth = 0;
    mHeight = 0;

    mQuit = false;
}

Window::~Window()
{
    free();
}

//ACCESS WINDOW ONLY THROUGH HERE
//Returns the singular window object instance
Window* Window::getInstance()
{
    return mInstance ? mInstance : (mInstance = new Window);
}

//Initializing the window and renderer
//Returns true if both window and renderer initialized successfully
bool Window::init()
{
    mWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(mWindow){
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;

        // SCALEX = mWidth / SCREEN_WIDTH;
        // SCALEY = mHeight / SCREEN_HEIGHT;
        // prevScaleX = SCALEX;
        // prevScaleY = SCALEY;

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(!mRenderer){
            std::cout << "Renderer not created! Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(mWindow);
            mWindow = nullptr;
        }
        else{
            mWindowDisplayID = SDL_GetWindowDisplayIndex(mWindow);

            mShown = true;
        }
    }
    else{
        std::cout << "Error! Window not created. Error: " << SDL_GetError() << std::endl; 
    }

    return mWindow != nullptr && mRenderer != nullptr;
}

//Handles basic events for the window
void Window::handleEvent(SDL_Event &e)
{
    if(e.type == SDL_WINDOWEVENT){
        switch(e.window.event){
            //check for display change if window moved
            case SDL_WINDOWEVENT_MOVED:
            mWindowDisplayID = SDL_GetWindowDisplayIndex(mWindow);
            break;

            //check if the size was changed
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWidth = e.window.data1;
            mHeight = e.window.data2;
            // SCALEX = mWidth / (SCREEN_WIDTH);
            // SCALEY = mHeight / (SCREEN_HEIGHT);
            // prevScaleX = SCALEX;
            // prevScaleY = SCALEY;
            SDL_RenderPresent(mRenderer);

            //check if our window got exposed
            case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(mRenderer);
            break;

            //check if mouse entered/left the screen
            case SDL_WINDOWEVENT_ENTER:
            mMouseFocus = true;
            break;

            case SDL_WINDOWEVENT_LEAVE:
            mMouseFocus = false;
            break;

            //check if a different application is in front
            case SDL_WINDOWEVENT_FOCUS_GAINED:
            mKeyboardFocus = true;
            break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
            mKeyboardFocus = false;
            break;

            //check if window was minimized, maximized, or restored from being minimized
            case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

            case SDL_WINDOWEVENT_MAXIMIZED:
            mMinimized = false;
            break;

            case SDL_WINDOWEVENT_RESTORED:
            mMinimized = false;
            break;
        }
    }
    else if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_F1){
            if(mFullScreen){
                SDL_SetWindowFullscreen(mWindow, false);
                mFullScreen = false;
            }
            else{
                SDL_SetWindowSize(mWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
                SDL_SetWindowFullscreen(mWindow, true);
                mFullScreen = true;
                mMinimized = false;
            }
        }
        else if(e.key.keysym.sym == SDLK_F2){
            std::cerr << mWidth << ", " << mHeight << std::endl;
        }
    }
}

//Destroys window and renderer
void Window::free()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    mWindow = nullptr;
    mRenderer = nullptr;

    mShown = false;
    mMinimized = false;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;

    mWidth = 0;
    mHeight = 0;
}

//access to the renderer
SDL_Renderer* Window::getRenderer()
{
    return mRenderer;
}

//access to the window
SDL_Window* Window::getWindow()
{
    return mWindow;
}

int Window::getWidth()
{
    return mWidth;
}

int Window::getHeight()
{
    return mHeight;
}

bool Window::hasMouseFocus()
{
    return mMouseFocus;
}

bool Window::hadKeyboardFocus()
{
    return mKeyboardFocus;
}

bool Window::isMinimized()
{
    return mMinimized;
}

bool Window::isShown()
{
    return mShown;
}

bool Window::isFullscreen()
{
    return mFullScreen;
}