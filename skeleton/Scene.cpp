#include "Scene.h"

Scene::Scene()
{
	setup();
}

Scene::~Scene()
{
}

void Scene::update(double t)
{
	// Actualiza todas las particulas
	for (int i = 0; i < objects.size(); i++) {

		// Si el update devuelve false es que la particula ha muerto por lo que la elimina y la quita del vector
		objects[i]->update(t);

		if (!objects[i]->getAlive()) {
			Particle* deadParticle = objects[i];

			// Notificar al generador, si existe
			if (particleToGenerator.find(deadParticle) != particleToGenerator.end()) {
				ParticleGenerator* generator = particleToGenerator[deadParticle];
				generator->onParticleDeath(deadParticle);
				particleToGenerator.erase(deadParticle);
			}

			// Eliminar la particula
			delete deadParticle;
			objects.erase(objects.begin() + i);
			i--;
		}
	}

	//actualizacion de los sistemas
	for (auto s : systems)
	{
		s->update(t);
		s->affectParticles(objects);
	}
}

void Scene::addParticle(Particle* obj, ParticleGenerator* gen)
{
	objects.push_back(obj);

	// Si la particula viene de un generador
	if (gen) {
		particleToGenerator[obj] = gen; // Asociar particula con su generador
	}
}

void Scene::addSystem(System* sys)
{
	systems.push_back(sys);
}

void Scene::show()
{
	for (auto p : objects)
		p->setVisibility(true);
	active = true;
}

void Scene::hide()
{
	for (auto p : objects)
		p->setVisibility(false);
	active = false;
}
