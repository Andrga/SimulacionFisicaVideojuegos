#pragma once
#include "Particle.h"
#include "Widget.h"
#include <PxPhysicsAPI.h>
#include <vector>
#include <unordered_map>
#include "../Global.h"

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
	virtual void affectParticles(unordered_map<string, GameObjectInfo> const & gameObjects, double t) {}
};

