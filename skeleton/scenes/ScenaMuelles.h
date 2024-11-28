#pragma once
#include "../basics/Scene.h"
#include "../systems/ParticleSystem.h"
#include "../systems/ForceSystem.h"

class ScenaMuelles : public Scene
{
private:
	ExplosionGenerator* expls = nullptr;
public:
	ScenaMuelles() : Scene() {};
	~ScenaMuelles() {};

	void setup() override;

	void keyPressed(unsigned char key, const physx::PxTransform& camera);
};