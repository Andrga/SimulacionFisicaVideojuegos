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

	// M�todo virtual para afectar part�culas (opcional para sistemas que no lo necesiten)
	virtual void affectParticles(vector<Particle*>& particles) {}
};

