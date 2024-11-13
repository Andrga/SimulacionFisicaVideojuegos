#pragma once
#include <vector>
#include "ParticleGenerator.h"
#include "System.h"

using namespace std;

class ParticleSystem : public System
{
private:
	vector<ParticleGenerator*> particleGenerators;

public:
	ParticleSystem();
	~ParticleSystem();

	bool update(double t) override;

	void addParticleGenerator(ParticleGenerator* partGen);
};

