#include "ParticleGenerator.h"


ParticleGenerator::ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys) : origen(org), startNParticles(stNpart), particleSystem(partsys)
{
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::setVisibility(bool visibility)
{
	for (auto p : particles) {
		p->setVisibility(visibility);
	}
}

void ParticleGenerator::update(double t)
{
	// Genera particulas si hace falta
	if (mayGenerate()) {
		generateParticle();
	}

	// Actualiza todas las particulas
	for (int i = 0; i < particles.size(); i++) {

		// Si el update devuelve false es que la particula ha muerto por lo que la elimina y la quita del vector
		particles[i]->update(t);
	}

	// eliminacion de particulas muertas
	for (int i = 0; i < particles.size(); i++) {

		if (!particles[i]->getAlive())
		{
			// Elimina la particula
			delete particles[i];
			// Encuentra la particula y elimina la referencia del vector
			auto ref = std::find(particles.begin(), particles.end(), particles[i]);
			particles.erase(ref);
			nParticles--;
			i--;
		}
	}

}

bool ParticleGenerator::mayGenerate()
{
	return nParticles <= startNParticles;
}

void ParticleGenerator::generateParticle() {

	cout << "---Nueva particula generada del sistema---" << endl;
}
