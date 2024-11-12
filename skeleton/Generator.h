#pragma once
#include "Particle.h"
#include <random>

class System;

class Generator
{
protected:
	//Particle particleReference;
	std::default_random_engine generator;

	// Propiedades inicio
	Vector3 origen;

	// Current particles
	vector<Particle*> particles;

public:
	Generator(Vector3 org, int stNpart, System* partsys);
	~Generator();


	virtual void generateParticle();

	void update(double t);
};

