#pragma once
#include "Modulo.h"

class ParticleSystem;
class ForceSystem;
class PropulsionParticleGen;
class ForceGenerator;

class Spaceship
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
	vector<PxFixedJoint*> fixedjoints;
	bool explotado = false;
	ParticleSystem* psys = nullptr;
	ForceSystem* fsys = nullptr;

	float porcentajeFuerzProp = 1;
	Vector3 DirPropulsion = { 0,0,0 };

	RBDynamic* parachute = nullptr;
	bool paracaActivo = false;
	ForceGenerator* forcGenParac = nullptr;
	string actualPlanet = "";

	// metodos privados
	Modulo* montarCoheteRec(ModuloInfo* modulo, Modulo* actualMod, PxPhysics* gPhysics, PxScene* gScene);
	Modulo* creaModulo(ModuloInfo* modulo, Modulo* actualMod, Vector3 posRelativa, PxPhysics* gPhysics, PxScene* gScene);
	void startParachute();
	void stopParachute();
public:
	Spaceship(Scene* scn, ParticleSystem* psistm, ForceSystem* forcstm, PxPhysics* gPhysx, PxScene* gScn);
	~Spaceship();

	float getCombustible() const noexcept { return combustible; };
	float getPorcPropulsion() const noexcept { return porcentajeFuerzProp; };
	Vector3 getPosition() const { return cabina->getPosition(); };
	Vector3 getDirection() const { return cabina->getRotation().rotate({ 0,1,0 }); };
	PxQuat getRotation() const { return cabina->getRotation(); };
	string getPlanet() const { return actualPlanet; };

	void setPorcPropulsion(float prop) noexcept { porcentajeFuerzProp = prop; };
	void setPlanet(string plt) { actualPlanet = plt; };

	void startParticles();
	void stopParticles();

	void useParachute();

	void explote();


	void propulsar(Vector3 dir);

};

