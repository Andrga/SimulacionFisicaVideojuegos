#pragma once
#include "../basics/Scene.h"


class ScenaSolidoRigido : public Scene
{
public:
	ScenaSolidoRigido(SceneManager* scnMang, physx::PxPhysics* gPhycs, physx::PxScene* gScn);
	~ScenaSolidoRigido();

	void setup()override;
};

