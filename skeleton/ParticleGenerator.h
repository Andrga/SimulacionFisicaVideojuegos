#pragma once
#include "Particle.h"
class ParticleGenerator
{
private:
	Particle particleReference;

	// Propiedades inicio
	int startNParticles;
	Vector3 startPos;
	Vector3 startVel;
	float startSize;
	Vector4 startColor;
	float startLifetime;

	// Current particles
	int nParticles = 0;

public:
	ParticleGenerator(Particle* partRef, int stNpart);
	~ParticleGenerator();

	Particle* generateParticle(Vector3 Pos = { 0,0,0 });
	bool mayGenerate();
};

