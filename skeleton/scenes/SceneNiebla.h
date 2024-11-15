#pragma once
#include "../basics/Scene.h"

#include "../basics/Proyectile.h"
#include "../systems/ParticleSystem.h"

#include "../systems/ForceSystem.h"
#include "../systems/ForceGenerator.h"

class SceneNiebla : public Scene
{
public:
	SceneNiebla() : Scene() {};
	~SceneNiebla() {};

	void setup() override;
};

