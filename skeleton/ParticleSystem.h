#pragma once
#include <vector>
#include "ParticleGenerator.h"
#include "Scene.h"

using namespace std;

class ParticleSystem : public Object
{
private:
	vector<ParticleGenerator*> particleGenerators;
	Scene* scene;

public:
	ParticleSystem(Scene* scn);
	~ParticleSystem();

	bool update(double t) override;

	void addParticleGenerator(ParticleGenerator* partGen);

	void setVisibility(bool visibility) override;
};

