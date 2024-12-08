#include "SceneNiebla.h"

void SceneNiebla::setup()
{
	//// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem(this);
	addSystem(partsyst);

	//------ Sistema 2 ------
	// sistema de particula niebla
	partsyst->addParticleGenerator(new NieblaGen(Vector3(0, 0, 0), 1000, partsyst, this));

	// --------- SISTEMA DE FUERZAS ------------
	ForceSystem* fSys = new ForceSystem(this);
	addSystem(fSys);

	// generador de viento
	VientoGenerador* vgen = new VientoGenerador({ 0,0,0 }, this, { 10,0,0 });
	fSys->addForceGenerator(vgen);

	vgen->setRadious(100);

	// generador de torvellino
	/*TorvellinoGenerator* tgen = new TorvellinoGenerator({ 0,0,0 });
	fSys->addForceGenerator(tgen);

	tgen->setRadious(30);*/
}
