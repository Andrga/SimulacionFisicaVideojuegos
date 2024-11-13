#pragma once
#include "Scene.h"

#include "Proyectile.h"
#include "ParticleSystem.h"
#include "Cascada.h"
#include "Niebla.h"
#include "Sangre.h"
#include "Disparo.h"

#include "ForceSystem.h"
#include "VientoGenerador.h"
class SceneParticleSystem : public Scene
{
public:
	SceneParticleSystem();
	~SceneParticleSystem();

	void setup() override;
};

