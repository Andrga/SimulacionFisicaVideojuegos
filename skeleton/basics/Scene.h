#pragma once
#include <vector>
#include "RBDynamic.h"
#include "RBStatic.h"
#include "Particle.h"
#include "System.h"
#include <unordered_map>
#include <typeinfo>
#include "../Global.h"

class SceneManager;

class Scene
{
protected:
	SceneManager* sceneManager;
	// Mapa objetos de juego 
	unordered_map<string, GameObjectInfo> gameObjects;
	// vector de sistemas
	vector<System*> systems;
	Camera* camera = nullptr;
	bool active = false;

	// escena fisica
	physx::PxPhysics* gPhysics = nullptr;
	physx::PxScene* gScene = nullptr;

public:
	Scene(SceneManager* scnMang, physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr);
	~Scene();

	virtual void setup() {};

	void update(double t);

	// Aniade particula al vector
	//void addParticle(Particle* prt, ParticleGenerator* gen = nullptr);
	// Aniade sistema al vector
	void addSystem(System* sys);
	// Aniade objeto al vector de objetos extra
	//void addObject(GameObject* obj);
	void addGameObject(GameObject* gob, ParticleGenerator* partGen = nullptr);
	// elimina un objeto
	void deleteGameObject(string name);


	// elimina un objeto de la escena
	void pxSceneVisivility(PxRigidActor* actor, bool vis);

	// metodo para comprobar si dos gameobjects se estan overlapeando
	bool checkColisions(GameObject* gb1, GameObject* gb2);

	// devuelve la cantidad de objetos en la escena
	int getGameObjectsCount() { return gameObjects.size(); }
	void show();
	void hide();

	virtual void keyPressed(unsigned char key, const physx::PxTransform& camera);
	// lanza una particula desde la camara hacia delante y devuelve el gameobject con el que ha chocado
	GameObject* rayCast(float mPosX, float mPosY);
};

