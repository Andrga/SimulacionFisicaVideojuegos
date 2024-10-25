#pragma once
#include "Particle.h"
#include <random>

class ParticleSystem;

class ParticleGenerator
{
protected:
	//Particle particleReference;
	std::default_random_engine generator;
	ParticleSystem* particleSystem;

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
	ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys);
	~ParticleGenerator();


	virtual void generateParticle();
	bool mayGenerate();
	int getNParticles() { return nParticles; }

	void update(double t);
};

