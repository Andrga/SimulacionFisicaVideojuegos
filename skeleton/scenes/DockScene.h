#pragma once
#include "../basics/Scene.h"
#include "../systems/ParticleSystem.h"
#include "../systems/ForceSystem.h"
#include "../systems/DockSystem.h"

class DockScene : public Scene
{
private:

public:
	DockScene() : Scene() {};
	~DockScene() {};

	void setup() override;

	void keyPressed(unsigned char key, const physx::PxTransform& camera) {};
};