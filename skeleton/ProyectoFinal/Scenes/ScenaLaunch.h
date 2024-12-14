#pragma once
#include "../../basics/Scene.h"
#include "../ObjetorsDeJuego/Modulo.h"
#include "../../systems/ForceSystem.h"
#include "../../systems/ForceGenerator.h"
#include "../../systems/ParticleSystem.h"
#include "../../systems/ParticleGenerator.h"

class ScenaLaunch : public Scene
{
protected:
	ForceSystem* fsys = nullptr;
	ParticleSystem* psys = nullptr;
	Modulo* cabina = nullptr;
	RBStatic* PlataformaLanzamiento = nullptr;

	// propulsion;
	vector<PropulsionParticleGen*> partGenerators;

	bool introPulsed = false;
	float porcentajeFuerzProp = 1;
	bool propulsando = false;
	Vector3 DirPropulsion = { 0,0,0 };

	Vector3 posIniCabina = { 0,0,0 };
	Vector3 cameraOffset = { 0,0, +100 };

	// cosas visuales
	float zoom = 0;
	float zoomVel = 10;
	float zoomFactor = 0;
	// velocidad del tiempo
	int timeFactor = 1;
public:
	ScenaLaunch(SceneManager* scnMang, physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr) : Scene(scnMang, gPhysics, gScene) {};
	~ScenaLaunch() {};
	void setup();

	void montarCohete();
	Modulo* montarCoheteRec(ModuloInfo* modulo, Modulo* actualMod);
	void propulsar(Vector3 impulseRotation);

	void keyPressed(unsigned char key, const physx::PxTransform& camera) override;
	void keyReleased(unsigned char key, const physx::PxTransform& camera) override;

	void update(double t) override;
	void show() override;
};

