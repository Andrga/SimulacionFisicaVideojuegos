#include "SceneNiebla.h"

SceneNiebla::SceneNiebla()
{
}

SceneNiebla::~SceneNiebla()
{
}

void SceneNiebla::setup()
{
	// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem(this);
	addSystem(partsyst);

	//------ Sistema 2 ------
	// sistema de particula niebla
	partsyst->addParticleGenerator(new Niebla(Vector3(0, 0, 0), 1000, partsyst));
}
