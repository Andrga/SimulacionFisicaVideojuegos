#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::update(double t)
{
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
}
void Scene::addObject(Object* obj)
{
	objects.push_back(obj);
}
