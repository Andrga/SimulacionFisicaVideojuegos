#pragma once
#include "../basics/Scene.h"

#include "../basics/Proyectile.h"
#include "../systems/ParticleSystem.h"

#include "../systems/ForceSystem.h"
#include "../systems/ForceGenerator.h"

class ScenaViento : public Scene
{
public:
	ScenaViento(Camera* cam) : Scene(cam) {};
	~ScenaViento() {};

	void setup() override;
};
