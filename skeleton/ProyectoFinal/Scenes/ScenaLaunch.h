#pragma once
#include "../../basics/Scene.h"
#include "../ObjetorsDeJuego/Cohete.h"	
#include "../ObjetorsDeJuego/Planeta.h"	
#include "../../systems/ForceSystem.h"
#include "../../systems/ForceGenerator.h"
#include "../../systems/ParticleSystem.h"
#include "../../systems/ParticleGenerator.h"
#include <iomanip>

class ScenaLaunch : public Scene
{
protected:
	ForceSystem* fsys = nullptr;
	ParticleSystem* psys = nullptr;
	Spaceship* spaceship = nullptr;
	RBStatic* PlataformaLanzamiento = nullptr;

	bool introPulsed = false;
	bool propulsando = false;

	Vector3 cameraOffset = { 0,0, +100 };

	vector<Planeta*> planetas;

	// cosas visuales
	float zoom = 0;
	float zoomVel = 1000;
	float zoomFactor = 0;

	void mostrarDirCohete(Vector3 dir);
public:
	ScenaLaunch(SceneManager* scnMang, physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr) : Scene(scnMang, gPhysics, gScene) {};
	~ScenaLaunch();
	void setup();

	void keyPressed(unsigned char key, const physx::PxTransform& camera) override;
	void keyReleased(unsigned char key, const physx::PxTransform& camera) override;

	void update(double t) override;
	void show() override;

	void exploteSpaceship();
	void setPlaneta(string plt) { spaceship->setPlanet(plt); };
};

