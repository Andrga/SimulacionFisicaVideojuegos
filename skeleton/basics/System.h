#pragma once
#include "Particle.h"
#include "Widget.h"
#include <PxPhysicsAPI.h>
#include <vector>

using namespace std;
class Scene;

class System
{
protected:
	double delta = 0;
	Scene* scene = nullptr;
public:
	System(Scene* scn):scene(scn) {};
	~System() {};

	virtual bool update(double t) {
		delta = t;
		return false;
	};

	double getDelta() { return delta; }
	// Método virtual para afectar partículas (opcional para sistemas que no lo necesiten)
	virtual void affectParticles(vector<Particle*>& particles, double t) {}
};

