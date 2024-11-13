#include "Disparo.h"
#include "Scene.h"

Disparo::Disparo(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(org, nparts, partsys, scn)
{
}

Disparo::~Disparo()
{
}

void Disparo::generateParticle()
{
	int restParticles = (startNParticles - nParticles) / 2;
	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles

	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++) {

		// creamos la nueva particula
		Particle* aux = new Particle(origen, { 0,0,50 }, 0.5);
		aux->setStartLifeTime(1);
		// aniaadimos las particulas a la lista
		generatedParticles[aux] = true; // Aniaadir al mapa
		scene->addParticle(aux, this); // Aniaadir a la escena y pasar referencia del generador
		nParticles++;

	}
}
