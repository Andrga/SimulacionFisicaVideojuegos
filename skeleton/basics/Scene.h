#pragma once
#include <vector>
#include "Particle.h"
#include "System.h"
#include "../systems/ParticleGenerator.h"

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

public:
	Scene();
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
};

