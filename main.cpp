#include "GameState.h"
#include "Statehandler.h"

bool init()
{
    bool success(true);
    
    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        std::cout << "Error initializing SDL! Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else{
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        if(!Window::getInstance()->init()){
            std::cout << "Error initializing window!" << std::endl;
            success = false;
        }
        else{
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)){
                std::cout << "Error initializing IMG! Error: " << IMG_GetError() << std::endl;
                success = false;
            }

            if(TTF_Init() == -1){
                std::cout << "Error initializing TTF! Error: " << TTF_GetError() << std::endl;
                success = false;
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success(true);

    gFont = TTF_OpenFont("assets\\ARCADE.TTF", 36);
    if(!gFont){
        std::cout << "Error opening font! Error: " << TTF_GetError() << std::endl;
        success = false;
    }
    
    return success;
}

void close()
{
    Window::getInstance()->free();
    TTF_CloseFont(gFont);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

int main(int argc, char* argv[])
{
    if(!init()){
        std::cout << "Error init!" << std::endl;
    }
    else{
        if(!loadMedia()){
            std::cout << "Error loadMedia!" << std::endl;
        }
        else{
            bool quit=false;

            SDL_Event e;

            Statehandler game;

            while(!Window::getInstance()->mQuit){
                while(SDL_PollEvent( &e ) != 0){
                    if(e.type == SDL_QUIT){
                        Window::getInstance()->mQuit = true;
                    }
                    
                    Window::getInstance()->handleEvent(e);
                    game.handleEvents(e);
                }

                game.doLogic();

                if(!Window::getInstance()->isMinimized()){
                    SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), 32, 32, 32, 255);
                    SDL_RenderClear(Window::getInstance()->getRenderer());

                    game.render();

                    SDL_RenderPresent(Window::getInstance()->getRenderer());
                }
            }
        }
    }
    close();

    return 0;
}