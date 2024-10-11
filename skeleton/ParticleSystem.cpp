#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Particle* partMod, int sNParticles, Vector3 Pos, Vector3 Vel, float size, Vector4 color):
	particleModel(partMod), startNParticles(sNParticles), startPos(Pos), startVel(Vel), startSize(size), startColor(color)
{
}

void ParticleSystem::Update(float t)
{
	for(auto e: particles)
}
