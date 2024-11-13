#pragma once
#include <vector>
#include "Particle.h"
#include "System.h"
#include "ParticleGenerator.h"

class Scene
{
protected:
	vector<Particle*> objects; 
	std::unordered_map<Particle*, ParticleGenerator*> particleToGenerator; // Mapa para referencia opcional

	vector<System*> systems;

	bool active = false;

public:
	Scene();
	~Scene();

	virtual void setup() {};

	void update(double t);

	void addParticle(Particle* obj, ParticleGenerator* gen = nullptr);
	void addSystem(System* sys);
	// activa y desactiva la escena
	void show();
	void hide();
};

