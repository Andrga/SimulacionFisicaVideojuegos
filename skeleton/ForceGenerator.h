#pragma once
#include "Particle.h"
#include <random>

class ForceSystem;

class ForceGenerator
{
protected:
	//Particle particleReference;
	std::default_random_engine generator;

	// Propiedades inicio
	int startNParticles;
	Vector3 origen;
	Vector3 startVel;
	float startLifetime;


	float startSize;
	Vector4 startColor;

	// Current particles
	int nParticles = 0;
	vector<Particle*> particles;

public:
	ForceGenerator(Vector3 org, int stNpart);
	~ForceGenerator();


	virtual void generateForce();
	bool mayGenerate();

	void update(double t);
};

