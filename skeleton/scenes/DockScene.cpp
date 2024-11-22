#include "DockScene.h"

void DockScene::setup()
{
	DockSystem* dkSys = new DockSystem();

	Particle* part1= new Particle({ 0,10,0 });
	Particle* part2 = new Particle({ 0,0,0 });
	part2->applyGravity();

	dkSys->addDock(part1, part2, 1, 10);

	addParticle(part1);
	addParticle(part2);

	addSystem(dkSys);
}
