#include "SceneParticleSystem.h"

SceneParticleSystem::SceneParticleSystem(): Scene()
{}

SceneParticleSystem::~SceneParticleSystem()
{}

void SceneParticleSystem::setup()
{
	// ----- PARTICULA -----
	//addParticle( new Particle({0,0,0}, {0,1,0}, {0,10,0}, 0.98));
	// ----- PROYECTIL -----
	//scene->addObject(new Proyectile({ 0,0,0 }, { 25,25,0 }));


	// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem();
	addSystem(partsyst);


	//------ Sistema 4 ------
	// sistema de particula cascada
	partsyst->addParticleGenerator(new Cascada(Vector3(0, 50, 0), 10000, partsyst, this));

	//------ Sistema 2 ------
	// sistema de particula niebla
	//partsyst->addParticleGenerator(new Niebla(Vector3(0, 0, 0), 1000, partsyst));

	// ------ Sistema 3 -----
	// sistema de particula disparo
	//partsyst->addParticleGenerator(new Disparo(Vector3(0, 10, 0), 10, partsyst));
	// sistema de particula sangre
	//partsyst->addParticleGenerator(new Sangre(Vector3(0, 10, 50), 15, partsyst));
	
	// --------- SISTEMA DE FUERZAS ------------
	ForceSystem* fSys = new ForceSystem();
	addSystem(fSys);

	// generador de viento
	VientoGenerador* vgen = new VientoGenerador({ 0,0,0 }, { 5,0,0 });
	fSys->addForceGenerator(vgen);

	vgen->setRadious(20);
}
