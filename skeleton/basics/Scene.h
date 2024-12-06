#pragma once
#include <vector>
#include "Particle.h"
#include "System.h"
#include "../systems/ParticleGenerator.h"
#include "../basics/RBDynamic.h"
#include "../basics/RBStatic.h"

class Scene
{
protected:
	// vector de particulas
	vector<Particle*> particles;
	// vector para particulas generadas por un generador (para llevar el conteo de estas)
	std::unordered_map<Particle*, ParticleGenerator*> particleToGenerator; // Mapa para referencia opcional
	// vector de sistema de particulas
	vector<System*> systems;
	// vector de objetos extra
	vector<Object*> objects;

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
	void addParticle(Particle* prt, ParticleGenerator* gen = nullptr);
	// Aniade sistema al vector
	void addSystem(System* sys);
	// Aniade objeto al vector de objetos extra
	void addObject(Object* obj);
	// activa y desactiva la escena
	void show();
	void hide();

	virtual void keyPressed(unsigned char key, const physx::PxTransform& camera) {};
};

