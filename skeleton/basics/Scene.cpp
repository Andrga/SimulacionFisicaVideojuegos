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


	//cout << "TIEMPO ENTRE UPDATES: " << t << endl;
	vector<string> objetosEliminar;
	for (auto ob : gameObjects) {
		if (ob.second.gameObject == nullptr) {
			objetosEliminar.push_back(ob.second.gameObject->getName());
			continue;
		}

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

void Scene::addSystem(System* sys)
{
	systems.push_back(sys);
}


void Scene::addGameObject(GameObject* gob, ParticleGenerator* partGen)
{
	if (gameObjects.count(gob->getName())) {
		std::cout << "YA EXISTE ESTE OBJETO" << std::endl;
		gob->setName(gob->getName() + "(1)");
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
	delete gbInfo->second.gameObject;
	gameObjects.erase(name);
	std::cout << "objeto eliminado: " << name << endl;
}

void Scene::pxSceneVisivility(PxRigidActor* actor, bool vis)
{
	vis ?
		gScene->addActor(*actor) :
		gScene->removeActor(*actor);
}

void Scene::show()
{
	update(0);

	for (auto go : gameObjects)
		go.second.gameObject->setVisibility(true);

	active = true;
}

void Scene::hide()
{
	for (auto go : gameObjects)
		go.second.gameObject->setVisibility(false);

	active = false;
}
