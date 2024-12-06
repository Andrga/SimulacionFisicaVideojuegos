#include "Scene.h"

Scene::Scene(physx::PxPhysics* gPhycs, physx::PxScene* gScn): gPhysics(gPhycs), gScene(gScn)
{
	setup();
}

Scene::~Scene()
{
}

void Scene::update(double t)
{
	// si no esta activa la escena no updatea
	if (!active) return;

	// Actualiza todas las particulas
	for (int i = 0; i < particles.size(); i++) {

		// Si el update devuelve false es que la particula ha muerto por lo que la elimina y la quita del vector
		particles[i]->update(t);
	}

	//actualizacion de los sistemas
	for (auto s : systems)
	{
		s->update(t);
		s->affectParticles(particles, t);
	}

	for (auto o : objects)
	{
		o->update(t);
	}

	// borrado de particulas
	for (int i = 0; i < particles.size(); i++) {

		if (!particles[i]->getAlive()) {
			Particle* deadParticle = particles[i];

			// Notificar al generador, si existe
			if (particleToGenerator.find(deadParticle) != particleToGenerator.end()) {
				ParticleGenerator* generator = particleToGenerator[deadParticle];
				generator->onParticleDeath(deadParticle);
				particleToGenerator.erase(deadParticle);
			}

			// Eliminar la particula
			delete deadParticle;
			particles.erase(particles.begin() + i);
			i--;
		}
	}

}

void Scene::addParticle(Particle* prt, ParticleGenerator* gen)
{
	particles.push_back(prt);

	// Si la particula viene de un generador
	if (gen) {
		particleToGenerator[prt] = gen; // Asociar particula con su generador
	}
}

void Scene::addSystem(System* sys)
{
	systems.push_back(sys);
}

void Scene::addObject(Object* obj)
{
	objects.push_back(obj);
}

void Scene::show()
{
	for (auto p : particles)
		p->setVisibility(true);
	for (auto o : objects)
		o->setVisibility(true);
	active = true;
}

void Scene::hide()
{
	for (auto p : particles)
		p->setVisibility(false);
	for (auto o : objects)
		o->setVisibility(false);
	active = false;
}
