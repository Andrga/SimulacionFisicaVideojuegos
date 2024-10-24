#pragma once
#include "Particle.h"
class ParticleGenerator
{
private:
	Particle particleReference;

	// Propiedades inicio
	int startNParticles;
	physx::PxTransform startTransform;
	Vector3 startVel;
	Vector3 startAcc;
	float startSize;
	Vector4 startColor;
	float startLifetime;

	// Current particles
	int nParticles = 0;
	vector<Particle*> particles;

public:
	ParticleGenerator(Particle* partRef, int stNpart);
	~ParticleGenerator();

	Particle* generateParticle(Vector3 Pos = { 0,0,0 });
	bool mayGenerate();
	int getNParticles() { return nParticles; }

	void update(double t);
};

