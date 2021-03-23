#include "ParticleFactory.h"

std::vector<ParticleType*> ParticleFactory::mTypeVec = {};
ParticleFactory* ParticleFactory::mInstance = nullptr;

ParticleFactory::ParticleFactory()
{
}

ParticleFactory* ParticleFactory::getInstance()
{
    return mInstance ? mInstance : (mInstance = new ParticleFactory);
}

ParticleType* ParticleFactory::getParticleType(const std::string &name, const std::string &path)
{
    for(int i=0; i < mTypeVec.size(); ++i){
        if(mTypeVec[i]->getName() == name){
            //std::cout << "Returned existing type: " << name << " at path "  << path << std::endl;
            return mTypeVec[i];
        }
    }

    mTypeVec.push_back(new ParticleType(name));
    mTypeVec[mTypeVec.size() - 1]->setTexture(path);
    //std::cout << "Returned new type: " << name << " at path " << path << std::endl;
    return mTypeVec[mTypeVec.size() - 1];
}