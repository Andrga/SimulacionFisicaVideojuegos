#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Scene* scn): scene(scn)
{

}

ParticleSystem::~ParticleSystem()
{
}

bool ParticleSystem::update(double t)
{
	for (auto e : particleGenerators)
	{
		if (e->mayGenerate()) {
			Particle* partAux = e->generateParticle();
			particles.push_back(partAux);
		}
	}

	int siz = particles.size();

	// Actualiza todas las particulas

	for (int i = 0; i < siz; i++) {

		// Si el update devuelve false es que la particula ha muerto por lo que la elimina y la quita del vector
		particles[i]->update(t);
	}

	for (int i = 0; i < siz; i++) {
		{
			if (!particles[i]->getAlive())
			{
				// Elimina la particula
				delete particles[i];
				// Encuentra la particula y elimina la referencia del vector
				auto ref = std::find(particles.begin(), particles.end(), particles[i]);
				particles.erase(ref);
				i--;
				siz--;
			}

		}
	}

	return true;
}

void ParticleSystem::addParticleGenerator(ParticleGenerator* partGen)
{
	particleGenerators.push_back(partGen);
}
