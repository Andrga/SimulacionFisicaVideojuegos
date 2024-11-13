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
	ParticleSystem* partsyst = new ParticleSystem();
	addSystem(partsyst);

	//------ Sistema 2 ------
	// sistema de particula niebla
	partsyst->addParticleGenerator(new Niebla(Vector3(0, 0, 0), 1000, partsyst, this));

	// --------- SISTEMA DE FUERZAS ------------
	ForceSystem* fSys = new ForceSystem();
	addSystem(fSys);

	// generador de viento
	VientoGenerador* vgen = new VientoGenerador({ 0,0,0 }, { 5,0,0 });
	fSys->addForceGenerator(vgen);

	vgen->setRadious(20);
}
