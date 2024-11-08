#include "Niebla.h"

Niebla::Niebla(Vector3 org, int nparts, ParticleSystem* partsys) : ParticleGenerator(org, nparts, partsys)
{
}

Niebla::~Niebla()
{
}

void Niebla::generateParticle()
{
	// cantidad de particulas no generadas
	int restParticles = (startNParticles / 2) - nParticles;

	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::uniform_int_distribution<int> posXZUniform(-20, 20); // numero de -10 a 10
	std::uniform_int_distribution<int> posYUniform(0, 40); // numero de 0 a 20

	std::normal_distribution<double> Bdistribution(10, 0.8); // numero de 0 a restParticles

	// origen de la nueva particula
	Vector3 origen2;
	// velocidad para la nueva particula
	Vector3 velocity;
	velocity.x = 1;
	velocity.y = 0;
	velocity.z = 0;
	// tiempo de vida para la nueva particula
	float lifetime;
	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++) {
		// aleatorizamos las variabes asignadas a las nuevas particulas
		origen2 = origen;
		origen2.x = posXZUniform(generator);
		origen2.y = posYUniform(generator);
		origen2.z = posXZUniform(generator);

		lifetime = Bdistribution(generator);

		// creamos la nueva particula
		Particle* aux = new Particle(origen2, velocity, .25, 1);
		aux->setStartLifeTime(lifetime);

		// añadimos las particulas a la lista
		particles.push_back(aux);
		nParticles++;

	}



}
