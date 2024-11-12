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
	if (!active) return;

	int siz = objects.size();

	// Actualiza todas las particulas

	for (int i = 0; i < siz; i++) {

		// Si el update devuelve false es que la particula ha muerto por lo que la elimina y la quita del vector
		objects[i]->update(t);
	}

	for (int i = 0; i < siz; i++) {

		if (!objects[i]->getAlive())
		{
			// Elimina la particula
			delete objects[i];
			// Encuentra la particula y elimina la referencia del vector
			auto ref = std::find(objects.begin(), objects.end(), objects[i]);
			objects.erase(ref);
			cout << "elimina scena" << endl;
			i--;
			siz--;
		}
	}

	//actualizacion de los sistemas
	for (auto s : systems)
		s->update(t);
}

void Scene::addParticle(Particle* obj)
{
	objects.push_back(obj);
}

void Scene::addSystem(Object* obj)
{
	systems.push_back(obj);
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
