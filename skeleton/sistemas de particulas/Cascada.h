#pragma once
#include "../systems/ParticleGenerator.h"
#include "../basics/Proyectile.h"

class Cascada : public ParticleGenerator
{

public:
	Cascada(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn);
	~Cascada();

	void generateParticle() override;
};

