#pragma once
#include "../../basics/Scene.h"
#include"../Basics/ObjetoMovible.h"

class ScenaMontaje : public Scene
{
private:
	const Vector3 CAMERA_START_POS = { 0,0,50 };
public:
	ScenaMontaje(SceneManager* scnMang, physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr) :
		Scene(scnMang, gPhysics, gScene) {};
	~ScenaMontaje() {};

	void setup()override;
	void show() override;
};

