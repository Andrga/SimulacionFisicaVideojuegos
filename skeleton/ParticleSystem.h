#pragma once
#include <vector>
#include "Particle.h"

using namespace std;

class ParticleSystem
{
private:
	Particle* particleModel;
	vector<Particle*> particles;

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
	ParticleSystem(Particle* partMod, int sNParticles = 1, Vector3 Pos = {0,0,0}, Vector3 Vel = {0,0,0}, 
		float size = 1, Vector4 color = {1,1,1,1});
	~ParticleSystem();

	virtual void Update(float t);
};

