#pragma once
#include "Particle.h"
#include <unordered_map>
#include <random>

class ParticleSystem;
class Scene;

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
	Scene* scene = nullptr;
	int nParticles = 0;
	std::unordered_map<Particle*, bool> generatedParticles; // Partículas generadas por este generador


public:
	ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn);
	~ParticleGenerator();


	virtual void generateParticle();
	bool mayGenerate();
	int getNParticles() { return nParticles; }
	void onParticleDeath(Particle* p); // Método para actualizar el conteo

	//void setVisibility(bool visibility);

	void update(double t);
};

