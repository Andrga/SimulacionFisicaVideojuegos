#pragma once
#include "ParticleGenerator.h"

class Niebla : public ParticleGenerator
{
public:
    Niebla(Vector3 org, int nparts, ParticleSystem* partsys);
    ~Niebla();

    void generateParticle() override;
};

