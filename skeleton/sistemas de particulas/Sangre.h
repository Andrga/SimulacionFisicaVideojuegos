#pragma once
#include "../systems/ParticleGenerator.h"
#include "../basics/Proyectile.h"
#include "iostream"

class Sangre: public ParticleGenerator
{
public:
	Sangre(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn);
	~Sangre();

	void generateParticle() override;
};

