#pragma once
#include "../basics/Scene.h"

#include "../basics/Proyectile.h"
#include "../systems/ParticleSystem.h"

#include "../systems/ForceSystem.h"

class SceneParticleSystem : public Scene
{
public:
	SceneParticleSystem(Camera* cam);
	~SceneParticleSystem();

	void setup() override;
};

