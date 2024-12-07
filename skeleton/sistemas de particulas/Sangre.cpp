#include "Sangre.h"
#include "../basics/Scene.h"

Sangre::Sangre(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(org, nparts, partsys, scn)
{
}

Sangre::~Sangre()
{
}

void Sangre::generateParticle()
{
	// cantidad de particulas no generadas
	int restParticles = (startNGameObjects  - nGameObjects)/2;

	// Generamos una cantidad de particulas, cuya cantidad entra en el rango de la capacidad de particulas maxima,
	// es decir restParticles
	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles

	std::normal_distribution<double> XnormalDistribution(0, 5.0); // media|dispersion
	std::normal_distribution<double> YnormalDistribution(5, 5.0); // media|dispersion
	std::normal_distribution<double> ZnormalDistribution(20, 2.0); // media|dispersion
	std::normal_distribution<double> LFEnormalDistribution(.5, 0.01); // media|dispersion

	// velocidad para la nueva particula
	Vector3 velocity;
	// tiempo de vida para la nueva particula
	float lifetime;

	for (int i = 0; i < startNGameObjects; i++) {
		velocity.y = YnormalDistribution(generator);
		velocity.x = XnormalDistribution(generator);
		velocity.z = ZnormalDistribution(generator);
		lifetime = LFEnormalDistribution(generator);

		Particle* aux = new Proyectile("Object" + scene->getGameObjectsCount(), scene, origen, velocity, 1);
		aux->setVelocity(velocity);
		aux->setSize(1);
		aux->setStartLifeTime(lifetime);
		generatedGameObjects[aux] = true; // Aniaadir al mapa
		scene->addGameObject(aux, this); // Aniaadir a la escena y pasar referencia del generador

		nGameObjects++;
	}


}
