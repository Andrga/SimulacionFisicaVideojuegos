#pragma once
#include "Particle.h"
#include <vector>

using namespace std;


class System
{
private:
	double delta = 0;
public:
	System() {};
	~System() {};

	virtual bool update(double t) {
		delta = t;
		return false;
	};

	double getDelta() { return delta; }
	// M�todo virtual para afectar part�culas (opcional para sistemas que no lo necesiten)
	virtual void affectParticles(vector<Particle*>& particles, double t) {}
};

