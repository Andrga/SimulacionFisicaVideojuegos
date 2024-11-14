#pragma once
#include "../basics/Scene.h"

#include "../basics/Proyectile.h"
#include "../systems/ParticleSystem.h"
#include "../sistemas de particulas/Niebla.h"

#include "../systems/ForceSystem.h"
#include "../systems/ForceGenerator.h"

class ScenaViento : public Scene
{
public:
	ScenaViento() : Scene() {};
	~ScenaViento() {};

	void setup() override;
};
