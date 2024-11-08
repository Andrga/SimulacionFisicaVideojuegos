#include "Disparo.h"

Disparo::Disparo(Vector3 org, int nparts, ParticleSystem* partsys): ParticleGenerator(org,nparts,partsys)
{
}

Disparo::~Disparo()
{
}

void Disparo::generateParticle()
{
	int restParticles = (startNParticles  - nParticles)/2;
	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles

	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++) {

		// creamos la nueva particula
		Particle* aux = new Particle(origen, {0,0,50}, 0.5, 1);
		aux->setStartLifeTime(1);
		// añadimos las particulas a la lista
		particles.push_back(aux);
		nParticles++;

	}
}
