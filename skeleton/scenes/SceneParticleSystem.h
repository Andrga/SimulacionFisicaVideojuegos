#pragma once
#include "../basics/Scene.h"

#include "../basics/Proyectile.h"
#include "../systems/ParticleSystem.h"
#include "../sistemas de particulas/Cascada.h"
#include "../sistemas de particulas/Niebla.h"
#include "../sistemas de particulas/Sangre.h"
#include "../sistemas de particulas/Disparo.h"

#include "../systems/ForceSystem.h"

class SceneParticleSystem : public Scene
{
public:
	SceneParticleSystem();
	~SceneParticleSystem();

	void setup() override;
};

