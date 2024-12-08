#pragma once
#include "../basics/Scene.h"
#include "../systems/ParticleSystem.h"
#include "../systems/ForceSystem.h"

class ScenaMuelles : public Scene
{
private:
	ExplosionGenerator* expls = nullptr;
	SpringGenerator* sprngGen = nullptr;
public:
	ScenaMuelles(Camera* cam) : Scene(cam) {};
	~ScenaMuelles() {};

	void setup() override;

	void keyPressed(unsigned char key, const physx::PxTransform& camera);
};