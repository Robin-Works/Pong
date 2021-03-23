#include "Global.h"
TTF_Font* gFont = nullptr;

double lerp(double x, double y, double weight)
{
    return x + weight * (y - x);
}