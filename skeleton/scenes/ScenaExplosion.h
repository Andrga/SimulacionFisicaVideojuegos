#pragma once
#include "../basics/Scene.h"

#include "../systems/ParticleSystem.h"
#include "../sistemas de particulas/Niebla.h"

#include "../systems/ForceSystem.h"
#include "../systems/ForceGenerator.h"

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