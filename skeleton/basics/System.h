#pragma once
#include "Particle.h"
#include <vector>

using namespace std;


class System
{
public:
	System() {};
	~System() {};

	virtual bool update(double t) { return false; };

	// Método virtual para afectar partículas (opcional para sistemas que no lo necesiten)
	virtual void affectParticles(vector<Particle*>& particles) {}
};

