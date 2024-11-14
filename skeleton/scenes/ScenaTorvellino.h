#pragma once
#include "../basics/Scene.h"

#include "../basics/Proyectile.h"
#include "../systems/ParticleSystem.h"
#include "../sistemas de particulas/Niebla.h"

#include "../systems/ForceSystem.h"
#include "../systems/ForceGenerator.h"

class ScenaTorvellino : public Scene
{
public:
	ScenaTorvellino() : Scene()  {};
	~ScenaTorvellino() {};

	void setup() override;
};
