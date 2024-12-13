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
	// si no esta activa la escena no updatea
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
	/*
	// Limites del cubo 1
	float x_min1 = posObj1.x - halfSide1, x_max1 = posObj1.x + halfSide1;
	float y_min1 = posObj1.y - halfSide1, y_max1 = posObj1.y + halfSide1;
	float z_min1 = posObj1.z - halfSide1, z_max1 = posObj1.z + halfSide1;

	// Limites del cubo 2
	float x_min2 = posObj2.x - halfSide2, x_max2 = posObj2.x + halfSide2;
	float y_min2 = posObj2.y - halfSide2, y_max2 = posObj2.y + halfSide2;
	float z_min2 = posObj2.z - halfSide2, z_max2 = posObj2.z + halfSide2;

	// Verifica si hay solapamiento en cada eje (x, y, z)
	bool overlapX = !(x_max1 < x_min2 || x_min1 > x_max2);
	bool overlapY = !(y_max1 < y_min2 || y_min1 > y_max2);
	bool overlapZ = !(z_max1 < z_min2 || z_min1 > z_max2);*/


	// overlapX || overlapY || overlapZ;//= physx::PxGeometryQuery::overlap(gb1->getShape()->getGeometry().any(), *gb1->getTransform(), gb2->getShape()->getGeometry().any(), *gb2->getTransform());

	/*if (col)
		cout << "HA OLISIONADO " << gb1->getName() << " con " << gb2->getName() << endl;*/
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
