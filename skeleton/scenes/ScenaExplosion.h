#pragma once
#include "../basics/Scene.h"
#include "../systems/ParticleSystem.h"
#include "../systems/ForceSystem.h"

class ScenaExplosion : public Scene
{
private:
	ExplosionGenerator* explosionGen = nullptr;
public:
	ScenaExplosion(SceneManager* scnMang) : Scene(scnMang) {};
	~ScenaExplosion() {};

	void setup() override;

	void keyPressed(unsigned char key, const physx::PxTransform& camera);
};