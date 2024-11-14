#pragma once
#include "../systems/ParticleGenerator.h"
class Disparo :
    public ParticleGenerator
{
public:
    Disparo(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn);
    ~Disparo();

    void generateParticle() override;
};

