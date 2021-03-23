#ifndef COLLIDER_H
#define COLLIDER_H

#include "Window.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include <string>

class Collider
{
public:
    Collider(const std::string &name, int x=0, int y=0, int w=0, int h=0);
    ~Collider();

    void setPos(int x, int y);

    void setDimensions(int w, int h);

    const std::string* checkCollision();

    SDL_Rect* getCollider(const std::string &name);
    SDL_Rect* getCollider();
private:
    //The objects collider, name, and unique collider id
    SDL_Rect mCollider;
    std::string mName;

    static std::vector<Collider*> mColliderVector;

    //helper function to add collider to the map when object is created
    void addCollider();
    void removeCollider();
};

#endif