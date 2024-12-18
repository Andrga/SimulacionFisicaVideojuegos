#pragma once
#include "Modulo.h"

class ParticleSystem;
class ForceSystem;
class PropulsionParticleGen;
class ForceGenerator;

class Cohete
{
private:
	Scene* scene = nullptr;
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	Modulo* cabina = nullptr;
	float combustible = 0;

	// propulsion;
	vector<PropulsionParticleGen*> partGenerators;
	vector<Modulo*> Propulsores;
	ParticleSystem* psys = nullptr;
	ForceSystem* fsys = nullptr;

	float porcentajeFuerzProp = 1;
	Vector3 DirPropulsion = { 0,0,0 };

	RBDynamic* parachute = nullptr;
	bool paracaActivo = false;
	ForceGenerator* forcGenParac = nullptr;

	Modulo* montarCoheteRec(ModuloInfo* modulo, Modulo* actualMod, PxPhysics* gPhysics, PxScene* gScene);
	Modulo* creaModulo(ModuloInfo* modulo, Modulo* actualMod, Vector3 posRelativa, PxPhysics* gPhysics, PxScene* gScene);
public:
	Cohete(Scene* scn, ParticleSystem* psistm, ForceSystem* forcstm, PxPhysics* gPhysx, PxScene* gScn);
	~Cohete();

	float getCombustible() const noexcept { return combustible; };
	float getPorcPropulsion() const noexcept { return porcentajeFuerzProp; };
	Vector3 getPosition() const { return cabina->getPosition(); };
	PxQuat getRotation() const { return cabina->getRotation(); };

	void setPorcPropulsion(float prop) noexcept { porcentajeFuerzProp = prop; };

	void startParticles();
	void stopParticles();

	void useParachute();
	void startParachute();
	void stopParachute();


	void propulsar(Vector3 dir);
};

