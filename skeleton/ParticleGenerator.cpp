#include "ParticleGenerator.h"
#include "Scene.h"

ParticleGenerator::ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn) : 
	origen(org), startNParticles(stNpart), particleSystem(partsys), scene(scn)
{
}

ParticleGenerator::~ParticleGenerator()
{
}


void ParticleGenerator::update(double t)
{
	// Genera particulas si hace falta
	if (mayGenerate()) {
		generateParticle();
	}
}

bool ParticleGenerator::mayGenerate()
{
	return nParticles <= startNParticles;
}

void ParticleGenerator::onParticleDeath(Particle* p) {
	if (generatedParticles.find(p) != generatedParticles.end()) {
		generatedParticles.erase(p); // Eliminar del mapa
		nParticles--;
	}
}

void ParticleGenerator::generateParticle() {

	cout << "---Nueva particula generada del sistema---" << endl;
}
