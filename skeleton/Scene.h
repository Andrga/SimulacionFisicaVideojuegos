#pragma once
#include <vector>

#include "Particle.h"

using namespace std;

class Scene
{
protected:
	vector<Particle*> particles;

public:
	Scene();
	~Scene();

	void update(double t);
	void addParticle(Particle* part);
};

