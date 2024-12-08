#pragma once
#include "../basics/Scene.h"

#include "../basics/Proyectile.h"
#include "../systems/ParticleSystem.h"

#include "../systems/ForceSystem.h"
#include "../systems/ForceGenerator.h"

class ScenaTorbellino : public Scene
{
public:
	ScenaTorbellino(Camera* cam) : Scene(cam)  {};
	~ScenaTorbellino() {};

	void setup() override;
};
