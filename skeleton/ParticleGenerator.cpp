#include "ParticleGenerator.h"


ParticleGenerator::ParticleGenerator(Particle* partRef, int stNpart): particleReference(*partRef), startNParticles(stNpart)
{
}

ParticleGenerator::~ParticleGenerator()
{
}

bool ParticleGenerator::mayGenerate()
{
	return nParticles < startNParticles;
}

Particle* ParticleGenerator::generateParticle(Vector3 Pos) {

	cout << "---Nueva particula generada del sistema---" << endl;
	nParticles++;
	Particle* aux = new Particle(particleReference);
	aux->setPosition(Pos);
	return aux;
}
