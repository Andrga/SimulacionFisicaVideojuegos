#include "Cascada.h"

Cascada::Cascada(Vector3 org, int nparts, ParticleSystem* partsys) :ParticleGenerator(org, nparts, partsys)
{
}

Cascada::~Cascada()
{
}

void Cascada::generateParticle()
{
	// cantidad de particulas no generadas
	int restParticles = (startNParticles / 2) - nParticles;

	// Generamos una cantidad de particulas, cuya cantidad entra en el rango de la capacidad de particulas maxima,
	// es decir restParticles
	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::normal_distribution<double> YnormalDistribution(5, 2.0); // media|dispersion
	std::normal_distribution<double> ZnormalDistribution(10, 2.0); // media|dispersion
	std::normal_distribution<double> LFEnormalDistribution(2, 10.0); // media|dispersion
	std::normal_distribution<double> ORGnormalDistribution(origen.x, 10.0); // media|dispersion

	// origen de la nueva particula
	Vector3 origen2;
	// velocidad para la nueva particula
	Vector3 velocity;
	velocity.x = 0;
	// tiempo de vida para la nueva particula
	float lifetime;
	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++) {
		// aleatorizamos las variabes asignadas a las nuevas particulas
		origen2 = origen;
		origen2.x = ORGnormalDistribution(generator);
		velocity.y = YnormalDistribution(generator);
		velocity.z = ZnormalDistribution(generator);
		lifetime = LFEnormalDistribution(generator);

		// creamos la nueva particula
		Particle* aux = new Proyectile(origen2, velocity, 0.5);
		aux->setStartLifeTime(lifetime);

		// añadimos las particulas a la lista
		particles.push_back(aux);
		nParticles ++;

	}



}
