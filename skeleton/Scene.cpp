#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::update(double t)
{
	for (Particle* e : particles) {

		e->update(t);
	}
}

void Scene::addParticle(Particle* part)
{
	particles.push_back(part);
}
