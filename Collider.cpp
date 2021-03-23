#include "Collider.h"

std::vector<Collider*> Collider::mColliderVector = {};

//initialize the collider
//name holds the unique name set to the collider, x, y, w, h set to 0 by default
Collider::Collider(const std::string &name, int x, int y, int w, int h)
{
    mCollider = {x, y, w, h};
    mName = name;

    this->addCollider();
}

Collider::~Collider()
{
    for(int i=0; i < mColliderVector.size(); ++i){
        if(mColliderVector[i]->mName == mName){
            //std::cout << "Deleting " << mColliderVector[i]->mName << " at " << i << std::endl;
            Collider *temp = mColliderVector[mColliderVector.size() - 1];
            mColliderVector[mColliderVector.size() - 1] = mColliderVector[i];
            mColliderVector[i] = temp;
            mColliderVector.pop_back();
        }
    }
}

//set position of collider
void Collider::setPos(int x, int y)
{
    mCollider.x = x;
    mCollider.y = y;
}

//set dimensions of collider
void Collider::setDimensions(int w, int h)
{
    mCollider.w = w;
    mCollider.h = h;
}

//check collisions between the object called upon and all other game colliders
//returns the name of the collider that was collided with, returns nullptr if not
const std::string* Collider::checkCollision()
{
        int leftMain, leftOther;
        int rightMain, rightOther;
        int topMain, topOther;
        int bottomMain, bottomOther;

        leftMain = mCollider.x;
        rightMain = mCollider.x + mCollider.w;
        topMain = mCollider.y;
        bottomMain = mCollider.y + mCollider.h;
    for(int i = 0; i < mColliderVector.size(); ++i){
        if(mColliderVector[i] == nullptr){
            std::cerr << "Erased the collider at " << i << std::endl;
            Collider *temp = mColliderVector[mColliderVector.size() - 1];
            mColliderVector[mColliderVector.size() - 1] = mColliderVector[i];
            mColliderVector[i] = temp;
            mColliderVector.pop_back();
        }
        else if(mName!= mColliderVector[i]->mName){
            leftOther = mColliderVector[i]->mCollider.x;
            rightOther = mColliderVector[i]->mCollider.x + mColliderVector[i]->mCollider.w;
            topOther = mColliderVector[i]->mCollider.y;
            bottomOther = mColliderVector[i]->mCollider.y + mColliderVector[i]->mCollider.h;

            if(((bottomMain <= topOther) || (topMain >= bottomOther) || (leftMain >= rightOther) || (rightMain <= leftOther)) == false){
                return &mColliderVector[i]->mName;
            }
        }
    }

    return nullptr;
}

//returns a collider from a specific name
//returns nullptr if name not in hashmap
SDL_Rect* Collider::getCollider(const std::string &name)
{
    for(int i = 0; i < mColliderVector.size(); ++i){
        if(mColliderVector[i]->mName == name){
            return &mColliderVector[i]->mCollider;
        }
    }

    return nullptr;
}

//returns collider from the object called upon
SDL_Rect* Collider::getCollider()
{
    for(int i =0; i < mColliderVector.size(); ++i){
        if(mName == mColliderVector[i]->mName){
            return &mColliderVector[i]->mCollider;
        }
    }

    return nullptr;
}

void Collider::addCollider()
{
    for(int i = 0; i < mColliderVector.size(); ++i){
        if(mColliderVector[i]->mName == mName){
            if(mColliderVector[i] == nullptr){
                Collider *temp = mColliderVector[mColliderVector.size() - 1];
                mColliderVector[mColliderVector.size() - 1] = mColliderVector[i];
                mColliderVector[i] = temp;
                mColliderVector.pop_back();
            }
            else{
                std::cerr << "Warning: Collision with key '" << mName << "' already exists in the collision map!" << std::endl;
                Collider *temp = mColliderVector[mColliderVector.size() - 1];
                mColliderVector[mColliderVector.size() - 1] = mColliderVector[i];
                mColliderVector[i] = temp;
                mColliderVector.pop_back();
            }
        }
    }

    mColliderVector.push_back(this);
}

