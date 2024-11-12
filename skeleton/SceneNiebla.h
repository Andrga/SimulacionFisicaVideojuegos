#pragma once
#include "Scene.h"

#include "Proyectile.h"
#include "ParticleSystem.h"
#include "Niebla.h"
class SceneNiebla :    public Scene
{
public:
	SceneNiebla();
	~SceneNiebla();

	void setup() override;
};

