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
public:
	ScenaLaunch(SceneManager* scnMang, physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr): Scene(scnMang, gPhysics, gScene) {};
	~ScenaLaunch() {};
	void setup();

	void montarCohete();
	Modulo* montarCoheteRec(ModuloInfo* modulo);
	void creaModulo();

	void update(double t) override;
	void show() override;
};

