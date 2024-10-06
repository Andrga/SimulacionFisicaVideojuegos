#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::update(double t)
{
	// Actualiza todas las particulas
	for (Particle* e : particles) {

		// Si el update devuelve false es que la particula ha muerto por lo que la elimina y la quita del vector
		if (!e->update(t))
		{
			// Elimina la particula
			delete e;
			// Encuentra la particula y elimina la referencia del vector
			auto ref = std::find(particles.begin(), particles.end(), e);
			particles.erase(ref);
		}
	}
}

void Scene::addParticle(Particle* part)
{
	particles.push_back(part);
}
