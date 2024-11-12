#pragma once
#include <vector>
#include "Particle.h"

class Scene
{
protected:
	vector<Particle*> objects;
	vector<Object*> systems;

	bool active = false;

public:
	Scene();
	~Scene();

	virtual void setup() {};

	void update(double t);
	void addParticle(Particle* obj);
	void addSystem(Object* obj);
	// activa y desactiva la escena
	void show();
	void hide();
};

