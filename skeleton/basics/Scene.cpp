#include "Scene.h"
#include "../systems/ParticleGenerator.h"

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
		if (o1.second.gameObject->getName().substr(0, 3) == "wid") continue;
		for (auto& o2 : gameObjects)
		{
			// si el objeto 1 y el objeto 2 son el mismo, o si el objeto2 es un widget ( no le afectan las colisiones) salta al sigiente
			if (o1.first == o2.first || o2.second.gameObject->getName().substr(0, 3) == "wid") continue;
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

	//actualizacion de los sistemas
	for (auto s : systems)
	{
		s->affectParticles(gameObjects, t);
		s->update(t);
	}

	for (auto n : objetosEliminar)
		deleteGameObject(n);
}

void Scene::addSystem(System* sys)
{
	systems.push_back(sys);
}


void Scene::addGameObject(GameObject* gob, ParticleGenerator* partGen)
{
	int nObj = 0;
	if (gameObjects.count(gob->getName())) {
		while (gameObjects.count(gob->getName() + "(" + to_string(nObj) + ")")) {
			nObj++;
			std::cout << "YA EXISTE ESTE OBJETO" << std::endl;
		}

		gob->setName(gob->getName() + "(" + to_string(nObj) + ")");
	}
	GameObjectInfo infogb;

	infogb = { gob, partGen };
	cout << "creado: " << gob->getName() << endl;
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

	// ANDRES AQUI, LA COLISION SOLO SE DETECTA CON UNA MITAD DEL OBJETO
	if (gb1 == nullptr || gb2 == nullptr)
		return false;
	// mitad del lado del bounding box
	Vector3 halfSide1 = gb1->getSize();
	Vector3 halfSide2 = gb2->getSize();

	Vector3 posObj1 = gb1->getPosition();
	Vector3 posObj2 = gb2->getPosition();

	bool col = (posObj1.x + halfSide1.x >= posObj2.x - halfSide2.x - 1 && posObj1.x - halfSide1.x <= posObj2.x + halfSide2.x + 1) &&
		(posObj1.y + halfSide1.y >= posObj2.y - halfSide2.y - 1 && posObj1.y - halfSide1.y <= posObj2.y + halfSide2.y + 1) &&
		(posObj1.z + halfSide1.z >= posObj2.z - halfSide2.z - 1 && posObj1.z - halfSide1.z <= posObj2.z + halfSide2.z + 1);

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
	update(0);
	for (auto go : gameObjects)
		go.second.gameObject->setVisibility(false);

	active = false;
}

void Scene::keyPressed(unsigned char key, const physx::PxTransform& camera)
{
	if (key == 13 && !enterPulsed) { enterPulsed = true; rayCast(); }
}

void Scene::keyReleased(unsigned char key, const physx::PxTransform& camera)
{
	if (key == 13) enterPulsed = false;
}

void Scene::mouseInput(int button, int state, int x, int y)
{
	//if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) rayCast(x, y);
}
/*
GameObject* Scene::rayCast(float mPosX, float mPosY)
{

	// PARA OTRO MOMENTO SI SE PUEDE

	//cout << "X: " << camera->getMouseWorldPos().x << " Y: " << camera->getMouseWorldPos().y << endl;
	//cout << "X: " << mPosX - glutGet(GLUT_SCREEN_WIDTH) / 2 << " Y: " << mPosY - glutGet(GLUT_SCREEN_HEIGHT) / 2 << endl;

	//// normalizacion de las coordenadas en la pantalla
	//float	nX = ((2 * mPosX) / glutGet(GLUT_SCREEN_WIDTH)) - 1,
	//	nY = 1 - ((2 * mPosY) / glutGet(GLUT_SCREEN_HEIGHT));

	//Vector3 direccion = camera->getDir() + Vector3(nX, nY, 1);

	//cout << "DIRECCION EN Z: " << direccion.z << endl;

	//// HAY QUE NORMALIZAR LA POSICION EN LA PANTALLA
	////
	//float velz = ((Vector3(0, 0, 0) - camera->getEye()) * PxVec3(1,0,0))

	Particle* particleRaycast = new Particle("Ray", this, camera->getMouseWorldPos());
	particleRaycast->setVelocity({ 0,0,-0.4 });
	particleRaycast->setStartLifeTime(1000);
	particleRaycast->setFloor(false);
	particleRaycast->setDamping(1);

	//particleRaycast->update(1);

	cout << particleRaycast->getPosition().x << "/" << particleRaycast->getPosition().y << "/" << particleRaycast->getPosition().z << endl;
	cout << camera->getEye().x << "/" << camera->getEye().y << "/" << camera->getEye().z << endl;
	// lanzamiento del raycast si golpea elimina la particula
	GameObject* golpeado = nullptr;


	while (particleRaycast->getAlive())
	{
		particleRaycast->update(0.5);

		for (auto& o2 : gameObjects)
		{
			// si el objeto2 es un widget ( no le afectan las colisiones) salta al sigiente
			if (typeid(o2.second.gameObject) == typeid(Widget*)) continue;
			//cout << particleRaycast->getPosition().x << "/" << particleRaycast->getPosition().y << "/" << particleRaycast->getPosition().z << endl;
			if (checkColisions(particleRaycast, o2.second.gameObject))
			{
				// llama a los metodos de colision de ambos objetos
				o2.second.gameObject->onCollision(particleRaycast);
				golpeado = o2.second.gameObject;
				particleRaycast->setAlive(false);
				cout << "HA COLISIONADO" << endl;
			}
		}
	}
	//cout << particleRaycast->getPosition().x << "/" << particleRaycast->getPosition().y << "/" << particleRaycast->getPosition().z << endl;

	delete particleRaycast;

	return golpeado;
}*/

GameObject* Scene::rayCast()
{
	// creacion de la particula que va a hacer de rayo
	Particle* particleRaycast = new Particle("ray", this, camera->getEye());
	particleRaycast->setSize({ 0.01,0.01,0.01 });
	particleRaycast->setVelocity(camera->getDir());
	particleRaycast->setStartLifeTime(1000);
	particleRaycast->setFloor(false);
	particleRaycast->setDamping(1);


	GameObject* golpeado = nullptr;


	while (particleRaycast->getAlive())
	{
		particleRaycast->update(0.5);

		for (auto& o2 : gameObjects)
		{
			// si el objeto2 es un widget ( no le afectan las colisiones) salta al sigiente
			if (o2.second.gameObject->getName().substr(0, 3) == "wid") continue;
			//cout << particleRaycast->getPosition().x << "/" << particleRaycast->getPosition().y << "/" << particleRaycast->getPosition().z << endl;
			if (checkColisions(particleRaycast, o2.second.gameObject))
			{
				// llama a los metodos de colision de ambos objetos
				o2.second.gameObject->onCollision(particleRaycast);
				golpeado = o2.second.gameObject;
				particleRaycast->setAlive(false);
				//cout << "HA COLISIONADO" << endl;
			}
		}
	}
	//cout << particleRaycast->getPosition().x << "/" << particleRaycast->getPosition().y << "/" << particleRaycast->getPosition().z << endl;

	delete particleRaycast;

	return golpeado;
}
