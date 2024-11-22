#pragma once
#include "../basics/Scene.h"
#include "../systems/ParticleSystem.h"
#include "../systems/ForceSystem.h"

class ScenaExplosion : public Scene
{
private:
	ExplosionGenerator* explosionGen = nullptr;
public:
	ScenaExplosion() : Scene() {};
	~ScenaExplosion() {};

	void setup() override;

	void keyPressed(unsigned char key, const physx::PxTransform& camera);
};