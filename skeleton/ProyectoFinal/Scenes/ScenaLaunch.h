#pragma once
#include "../../basics/Scene.h"
#include "../ObjetorsDeJuego/Modulo.h"
#include "../../systems/ForceSystem.h"
#include "../../systems/ForceGenerator.h"

class ScenaLaunch : public Scene
{
protected:
	ForceSystem* fsys = nullptr;
	Modulo* cabina = nullptr;

	float porcentajeFuerzProp = 1;

	Vector3 posIniCabina = { 0,0,0 };
public:
	ScenaLaunch(SceneManager * scnMang, physx::PxPhysics * gPhysics = nullptr, physx::PxScene * gScene = nullptr) : Scene(scnMang, gPhysics, gScene) {};
	~ScenaLaunch() {};
	void setup();

	void montarCohete();
	Modulo* montarCoheteRec(ModuloInfo* modulo, Modulo* actualMod);
	void propulsar();

	void keyPressed(unsigned char key, const physx::PxTransform& camera) override;

	void update(double t) override;
	void show() override;
};

