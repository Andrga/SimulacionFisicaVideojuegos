#include "ParticleGenerator.h"


ParticleGenerator::ParticleGenerator(Particle* partRef, int stNpart) : particleReference(*partRef), startNParticles(stNpart)
{
	startTransform = particleReference.getPose();
	startVel = particleReference.getVelocity();
	startAcc = particleReference.getAcceleration();
	startSize = particleReference.getSize();
	startLifetime = particleReference.getStartLifeTime();
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::update(double t)
{
	// Genera particulas si hace falta
	if (mayGenerate()) {
		particles.push_back(generateParticle());
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

Particle* ParticleGenerator::generateParticle(Vector3 Pos) {

	cout << "---Nueva particula generada del sistema---" << endl;
	nParticles++;
	Particle* aux = new Particle(startTransform.p, startVel, startAcc, 1, startSize, startLifetime);
	aux->setPosition(Pos);
	return aux;
}
