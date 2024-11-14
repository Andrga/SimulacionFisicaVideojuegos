#include "SceneNiebla.h"


SceneNiebla::SceneNiebla()
{
}

SceneNiebla::~SceneNiebla()
{
}

void SceneNiebla::setup()
{
	//// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem();
	addSystem(partsyst);

	//------ Sistema 2 ------
	// sistema de particula niebla
	partsyst->addParticleGenerator(new Niebla(Vector3(0, 0, 0), 1000, partsyst, this));
	
	
	/*Particle* part = new Particle({ 0,0,0 }, { 0,0,0 }, 1);
	addParticle(part);
	part->setStartLifeTime(10);
	part->setMass(100);*/


	// --------- SISTEMA DE FUERZAS ------------
	ForceSystem* fSys = new ForceSystem();
	addSystem(fSys);

	// generador de viento
	VientoGenerador* vgen = new VientoGenerador({ 0,0,0 }, { 10,0,0 });
	fSys->addForceGenerator(vgen);

	vgen->setRadious(20);
}
