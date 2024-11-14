#pragma once
#include "Scene.h"

#include "Proyectile.h"
#include "ParticleSystem.h"
#include "Niebla.h"

#include "ForceSystem.h"
#include "ForceGenerator.h"

class SceneNiebla : public Scene
{
public:
	SceneNiebla();
	~SceneNiebla();

	void setup() override;
};

