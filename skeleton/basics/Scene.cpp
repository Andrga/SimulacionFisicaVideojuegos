#include "Scene.h"

Scene::Scene(Camera* cam, physx::PxPhysics* gPhycs, physx::PxScene* gScn) : gPhysics(gPhycs), gScene(gScn), camera(cam)
{
	setup();
}

Scene::~Scene()
{
}

void Scene::update(double t)
{
	// si no esta activa la 
	// no updatea
	if (!active) return;

	// checkeo de colisiones

	for (auto& o1 : gameObjects)
	{
		for (auto& o2 : gameObjects)
		{
			if (o1.first == o2.first) continue;
			if (checkColisions(o1.second.gameObject, o2.second.gameObject))
			{
				o1.second.gameObject->onCollision(o2.second.gameObject);
				o2.second.gameObject->onCollision(o1.second.gameObject);
			}
		}
	}

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

	// en caso de que ya se hubiera eliminado
	if (gbInfo == gameObjects.end()) return;

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

bool Scene::checkColisions(GameObject* gb1, GameObject* gb2)
{
	if (gb1 == nullptr || gb2 == nullptr)
		return false;
	// mitad del lado del bounding box
	float halfSide1 = gb1->getSize() / 2;
	float halfSide2 = gb2->getSize() / 2;

	Vector3 posObj1 = gb1->getPosition();
	Vector3 posObj2 = gb2->getPosition();

	bool col =  (posObj1.x + halfSide1 >= posObj2.x && posObj1.x - halfSide1 <= posObj2.x + halfSide2) &&
		(posObj1.y + halfSide1 >= posObj2.y - halfSide2 && posObj1.y - halfSide1 <= posObj2.y + halfSide2) &&
		(posObj1.z + halfSide1 >= posObj2.z - halfSide2 && posObj1.z - halfSide1 <= posObj2.z + halfSide2);

	if (col)
		cout << "HA OLISIONADO " << gb1->getName() << " con " << gb2->getName() << endl;
	return col;
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
