#pragma once
#include <vector>
#include "RBDynamic.h"
#include "RBStatic.h"
#include "Particle.h"
#include "System.h"
#include <unordered_map>
#include "../Global.h"

class Scene
{
protected:
	// Mapa objetos de juego 
	unordered_map<string, GameObjectInfo> gameObjects;
	// vector de sistemas
	vector<System*> systems;

	bool active = false;

	// escena fisica
	physx::PxPhysics* gPhysics = nullptr;
	physx::PxScene* gScene = nullptr;

public:
	Scene(physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr);
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
	// activa y desactiva la escena
	void deleteGameObject(string name);

	int getGameObjectsCount() { return gameObjects.size(); }
	void show();
	void hide();

	virtual void keyPressed(unsigned char key, const physx::PxTransform& camera) {};
};

