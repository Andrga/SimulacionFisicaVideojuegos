#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Scene* scn) : scene(scn)
{

}

ParticleSystem::~ParticleSystem()
{
}

bool ParticleSystem::update(double t)
{
	for (auto e : particleGenerators)
	{
		e->update(t);
	}

	return true;
}

void ParticleSystem::addParticleGenerator(ParticleGenerator* partGen)
{
	particleGenerators.push_back(partGen);
}
