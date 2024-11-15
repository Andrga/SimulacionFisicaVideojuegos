#pragma once
#include "../basics/Scene.h"

#include "../basics/Proyectile.h"
#include "../systems/ParticleSystem.h"

#include "../systems/ForceSystem.h"
#include "../systems/ForceGenerator.h"

class ScenaTorbellino : public Scene
{
public:
	ScenaTorbellino() : Scene()  {};
	~ScenaTorbellino() {};

	void setup() override;
};
