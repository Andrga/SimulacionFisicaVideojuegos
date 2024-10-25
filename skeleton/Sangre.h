#pragma once
#include "ParticleGenerator.h"
#include "Proyectile.h"
#include "iostream"

class Sangre: public ParticleGenerator
{
public:
	Sangre(Vector3 org, int nparts, ParticleSystem* partsys);
	~Sangre();

	void generateParticle() override;
};

