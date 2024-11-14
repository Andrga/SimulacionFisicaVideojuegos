#pragma once
#include "../systems/ParticleGenerator.h"

class Niebla : public ParticleGenerator
{
public:
    Niebla(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn);
    ~Niebla();

    void generateParticle() override;
};

