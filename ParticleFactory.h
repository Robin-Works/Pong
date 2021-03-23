#ifndef PARTICLEFACTORY_H
#define PARTICLEFACTORY_H

#include <iostream>
#include <vector>
#include "ParticleTypes.h"

class ParticleFactory
{
public:
    static ParticleType* getParticleType(const std::string &name, const std::string &path);

    static ParticleFactory* getInstance();

private:
    static std::vector<ParticleType*> mTypeVec;

    ParticleFactory();

    static ParticleFactory* mInstance;
};

#endif