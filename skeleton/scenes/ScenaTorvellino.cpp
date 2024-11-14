#include "ScenaTorvellino.h"

void ScenaTorvellino::setup()
{
	// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem();
	addSystem(partsyst);

	// sistema de particula niebla
	partsyst->addParticleGenerator(new Niebla(Vector3(0, 0, 0), 1000, partsyst, this));

	// --------- SISTEMA DE FUERZAS ------------
	ForceSystem* fSys = new ForceSystem();
	addSystem(fSys);

	// generador de torvellino
	TorvellinoGenerator* tgen = new TorvellinoGenerator({ 0,0,0 }, this);
	fSys->addForceGenerator(tgen);

	tgen->setRadious(100);
}
