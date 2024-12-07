#include "Scene.h"

Scene::Scene(physx::PxPhysics* gPhycs, physx::PxScene* gScn) : gPhysics(gPhycs), gScene(gScn)
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
	/*
	// Actualiza todas las particulas
	for (int i = 0; i < particles.size(); i++) {

		// Si el update devuelve false es que la particula ha muerto por lo que la elimina y la quita del vector
		particles[i]->update(t);
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
				generator->onGameObjectDeath(deadParticle);
				particleToGenerator.erase(deadParticle);
			}

			// Eliminar la particula
			delete deadParticle;
			particles.erase(particles.begin() + i);
			i--;
		}
	}*/

	vector<string> objetosEliminar;
	for (auto ob : gameObjects) {
		ob.second.gameObject->update(t);

		if (!ob.second.gameObject->getAlive())
			objetosEliminar.push_back(ob.second.gameObject->getName());
	}

	for (auto n : objetosEliminar)
		deleteGameObject(n);

	//actualizacion de los sistemas
	for (auto s : systems)
	{
		s->update(t);
		s->affectParticles(gameObjects, t);
	}
}
/*
void Scene::addParticle(Particle* prt, ParticleGenerator* gen)
{
	particles.push_back(prt);

	// Si la particula viene de un generador
	if (gen) {
		particleToGenerator[prt] = gen; // Asociar particula con su generador
	}
}
void Scene::addObject(GameObject* obj)
{
	objects.push_back(obj);
}
*/

void Scene::addSystem(System* sys)
{
	systems.push_back(sys);
}


void Scene::addGameObject(GameObject* gob, ParticleGenerator* partGen)
{
	if (gameObjects.count(gob->getName())){
		std::cout << "YA EXISTE ESTE OBJETO" << std::endl;
		return;
	}
	GameObjectInfo infogb;

	infogb = { gob, partGen };

	gameObjects.insert({ gob->getName(), infogb });
}

void Scene::deleteGameObject(string name)
{
	auto gbInfo = gameObjects.find(name);

	// si esta atacchado a un sistema de particulas lo notifica para que elimine el gameobject
	if (gbInfo->second.partGen) {
		gbInfo->second.partGen->onGameObjectDeath(gbInfo->second.gameObject);
		gbInfo->second.partGen = nullptr; // para que no elimine el generador de particulas
	}
	gameObjects.erase(gbInfo);
	std::cout << "objeto eliminado: " << name << endl;
}

void Scene::show()
{
	update(0);
	/*for (auto p : particles)
		p->setVisibility(true);
	for (auto o : objects)
		o->setVisibility(true);*/

	for (auto go : gameObjects)
		go.second.gameObject->setVisibility(true);

	active = true;
}

void Scene::hide()
{
	/*for (auto p : particles)
		p->setVisibility(false);
	for (auto o : objects)
		o->setVisibility(false);*/

	for (auto go : gameObjects)
		go.second.gameObject->setVisibility(false);

	active = false;
}
