#include "ScenaExplosion.h"

void ScenaExplosion::setup()
{

	// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem();
	addSystem(partsyst);

	// denerador de particula niebla
	partsyst->addParticleGenerator(new Niebla(Vector3(0, 0, 0), 1000, partsyst, this));


	// --------- SISTEMA DE FUERZAS ------------
	ForceSystem* fSys = new ForceSystem();
	addSystem(fSys);

	// generador de viento
	ExplosionGenerator* egen = new ExplosionGenerator({ 0,0,0 }, this);
	fSys->addForceGenerator(egen);

	egen->setRadious(50);

	explosionGen = egen;
}

void ScenaExplosion::keyPressed(unsigned char key, const physx::PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		explosionGen->startGenerate();
		explosionGen->setRadious(10);
	default:
		break;
	}
}
