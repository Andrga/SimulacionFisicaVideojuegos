#pragma once
#include "../../basics/Scene.h"
#include"../Basics/ObjetoMovible.h"

class ScenaMontaje : public Scene
{
public:
	ScenaMontaje(SceneManager* scnMang, physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr) :
		Scene(scnMang, gPhysics, gScene) {};
	~ScenaMontaje() {};

	void setup()override;
};

