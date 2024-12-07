#include "Disparo.h"
#include "../basics/Scene.h"

Disparo::Disparo(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(org, nparts, partsys, scn)
{
}

Disparo::~Disparo()
{
}

void Disparo::generateParticle()
{
	int restParticles = (startNGameObjects - nGameObjects) / 2;
	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles

	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++) {

		// creamos la nueva particula
		Particle* aux = new Particle("Object" + scene->getGameObjectsCount(), scene, origen);
		aux->setVelocity({ 0,0,50 });
		aux->setSize(0.5);
		aux->setStartLifeTime(1);
		// aniaadimos las particulas a la lista
		generatedGameObjects[aux] = true; // Aniaadir al mapa
		scene->addGameObject(aux, this); // Aniaadir a la escena y pasar referencia del generador
		nGameObjects++;

	}
}
