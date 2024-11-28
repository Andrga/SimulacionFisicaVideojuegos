#include "ScenaTorbellino.h"

void ScenaTorbellino::setup()
{
	// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem(this);
	addSystem(partsyst);

	// sistema de particula niebla
	partsyst->addParticleGenerator(new RandomParticleGen(Vector3(0, 0, 0), 1000, partsyst, this));

	// --------- SISTEMA DE FUERZAS ------------
	ForceSystem* fSys = new ForceSystem(this);
	addSystem(fSys);

	// generador de torvellino
	TorbellinoGenerator* tgen = new TorbellinoGenerator({ 0,0,0 }, this);
	fSys->addForceGenerator(tgen);

	tgen->setRadious(100);
}
