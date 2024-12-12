#pragma once
#include "../../basics/Scene.h"
#include"../ObjetorsDeJuego/ObjetoMovible.h"
#include"../Basics/Button.h"

class ScenaMontaje : public Scene
{
private:
	const Vector3 CAMERA_START_POS = { 0,0,100 };
	ObjetoMovible* cabina = nullptr;
public:
	ScenaMontaje(SceneManager* scnMang, physx::PxPhysics* gPhysics = nullptr, physx::PxScene* gScene = nullptr) :
		Scene(scnMang, gPhysics, gScene) {};
	~ScenaMontaje() {};
	void update(double t) override;

	void setup()override;
	void show() override;

	void saveRocket();
	void LaunchScene();
};

