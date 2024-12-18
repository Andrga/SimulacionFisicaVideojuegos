#pragma once
#include "../../basics/Scene.h"
#include "../ObjetorsDeJuego/Cohete.h"	
#include "../../systems/ForceSystem.h"
#include "../../systems/ForceGenerator.h"
#include "../../systems/ParticleSystem.h"
#include "../../systems/ParticleGenerator.h"

class ScenaLaunch : public Scene
{
protected:
	ForceSystem* fsys = nullptr;
	ParticleSystem* psys = nullptr;
	//Modulo* cabina = nullptr;
	Cohete* cohete = nullptr;
	RBStatic* PlataformaLanzamiento = nullptr;

	bool introPulsed = false;
	bool propulsando = false;

	Vector3 cameraOffset = { 0,0, +100 };

	// cosas visuales
	float zoom = 0;
	float zoomVel = 10;
	float zoomFactor = 0;
	RBStatic* cameraAnchor1 = nullptr;
	RBDynamic* cameraAnchor2 = nullptr;
public:
	ScenaLaunch(SceneManager* scnMang, physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr) : Scene(scnMang, gPhysics, gScene) {};
	~ScenaLaunch();
	void setup();

	void keyPressed(unsigned char key, const physx::PxTransform& camera) override;
	void keyReleased(unsigned char key, const physx::PxTransform& camera) override;

	void update(double t) override;
	void show() override;
};

