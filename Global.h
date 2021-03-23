#ifndef GLOBAL_H
#define GLOBAL_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

extern TTF_Font* gFont;

extern double lerp(double x, double y, double weight);

#endif