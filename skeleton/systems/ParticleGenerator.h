#pragma once
#include "../basics/Particle.h"
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
	int startNGameObjects;
	Vector3 origen;
	Vector3 startVel;
	float startLifetime;


	float startSize;
	Vector4 startColor;

	// Current particles
	Scene* scene = nullptr;
	int nGameObjects = 0;
	int nGameObjectsTotal = 0;
	std::unordered_map<GameObject*, bool> generatedGameObjects; // Partículas generadas por este generador


public:
	ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn);
	~ParticleGenerator();


	virtual void generateParticle() = 0;
	bool mayGenerate();
	int getNParticles() { return nGameObjects; }
	void onGameObjectDeath(GameObject* p); // Método para actualizar el conteo

	//void setVisibility(bool visibility);

	void update(double t);
};

// --- GENERADOR DE CASCADA ---
class CascadaGen : public ParticleGenerator
{

public:
	CascadaGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(org, nparts, partsys, scn) {};
	~CascadaGen() {};

	void generateParticle() override;
};

// --- GENERADOR DE NIEBLA ---
class NieblaGen : public ParticleGenerator
{
public:
	NieblaGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(org, nparts, partsys, scn) {};
	~NieblaGen() {};

	void generateParticle() override;
};

// --- GENERADOR DE PARTICULAS DE VARIAS MASAS ---
class RandomParticleGen : public ParticleGenerator
{
public:
	RandomParticleGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(org, nparts, partsys, scn) {};
	~RandomParticleGen() {};

	void generateParticle() override;
};