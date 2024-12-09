#include "Scene.h"

Scene::Scene(SceneManager* scnMang, physx::PxPhysics* gPhycs, physx::PxScene* gScn) : gPhysics(gPhycs), gScene(gScn), camera(GetCamera()), sceneManager(scnMang)
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
		// si el objeto1 es un widget ( no le afectan las colisiones) salta al sigiente
		if (typeid(o1.second.gameObject) == typeid(Widget*)) continue;
		for (auto& o2 : gameObjects)
		{
			// si el objeto 1 y el objeto 2 son el mismo, o si el objeto2 es un widget ( no le afectan las colisiones) salta al sigiente
			if (o1.first == o2.first || typeid(o2.second.gameObject) == typeid(Widget*)) continue;
			if (checkColisions(o1.second.gameObject, o2.second.gameObject))
			{
				// llama a los metodos de colision de ambos objetos
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
	Vector3 halfSide1 = gb1->getSize();
	Vector3 halfSide2 = gb2->getSize();

	Vector3 posObj1 = gb1->getPosition();
	Vector3 posObj2 = gb2->getPosition();

	bool col = (posObj1.x + halfSide1.x >= posObj2.x && posObj1.x - halfSide1.x <= posObj2.x + halfSide2.x) &&
		(posObj1.y + halfSide1.y >= posObj2.y - halfSide2.y && posObj1.y - halfSide1.y <= posObj2.y + halfSide2.y) &&
		(posObj1.z + halfSide1.z >= posObj2.z - halfSide2.y && posObj1.z - halfSide1.z <= posObj2.z + halfSide2.z);

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

void Scene::keyPressed(unsigned char key, const physx::PxTransform& camera)
{

}

void Scene::mouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) rayCast(x, y);
}

GameObject* Scene::rayCast(float mPosX, float mPosY)
{
	cout << "X: " << mPosX << " Y: " << mPosY << endl;

	return nullptr;
}
