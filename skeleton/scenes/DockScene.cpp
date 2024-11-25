#include "DockScene.h"

void DockScene::setup()
{
	DockSystem* dkSys = new DockSystem();
	/*
		 1--2--3--4
		 |  |  |  |
		 5--6--7--8
		 |  |  |  |
		 9-10-11-12
		 |  |  |  |
		13-14-15-16
	*/

	Particle* part1 = new Particle({-10,10,-10});
	addParticle(part1);
	part1->setStartLifeTime(30);
	part1->setImmovible(true);
	Particle* part2 = new Particle({ -3.33,10,-10 });
	addParticle(part2);
	part2->setStartLifeTime(30);
	part2->applyGravity();
	Particle* part3 = new Particle({ 3.33,10,-10 });
	addParticle(part3);
	part3->setStartLifeTime(30);
	part3->applyGravity();
	Particle* part4 = new Particle({ 10,10,-10});
	addParticle(part4);
	part4->setStartLifeTime(30);
	part4->setImmovible(true);

	dkSys->addDock(part1, part2, 50, 1);
	dkSys->addDock(part2, part3, 50, 1);
	dkSys->addDock(part3, part4, 50, 1);


	Particle* part5 = new Particle({ -10,10,-3.3 });
	addParticle(part5);
	part5->setStartLifeTime(30);
	part5->applyGravity();
	Particle* part6 = new Particle({ -3.33,10,-3.3 });
	addParticle(part6);
	part6->setStartLifeTime(30);
	part6->applyGravity();
	Particle* part7 = new Particle({ 3.33,10,-3.3 });
	addParticle(part7);
	part7->setStartLifeTime(30);
	part7->applyGravity();
	Particle* part8 = new Particle({ 10,10,-3.3 });
	addParticle(part8);
	part8->setStartLifeTime(30);
	part8->applyGravity();

	dkSys->addDock(part5, part6, 50, 1);
	dkSys->addDock(part6, part7, 50, 1);
	dkSys->addDock(part7, part8, 50, 1);

	dkSys->addDock(part1, part5, 50, 1);
	dkSys->addDock(part2, part6, 50, 1);
	dkSys->addDock(part3, part7, 50, 1);
	dkSys->addDock(part4, part8, 50, 1);

	Particle* part9 = new Particle({ -10,10,3.3 });
	addParticle(part9);
	part9->setStartLifeTime(30);
	part9->applyGravity();
	Particle* part10 = new Particle({ -3.33,10,3.3 });
	addParticle(part10);
	part10->setStartLifeTime(30);
	part10->applyGravity();
	Particle* part11 = new Particle({ 3.33,10,3.3 });
	addParticle(part11);
	part11->setStartLifeTime(30);
	part11->applyGravity();
	Particle* part12 = new Particle({ 10,10,3.3 });
	addParticle(part12);
	part12->setStartLifeTime(30);
	part12->applyGravity();

	dkSys->addDock(part9, part10, 50, 1);
	dkSys->addDock(part10, part11, 50, 1);
	dkSys->addDock(part11, part12, 50, 1);

	dkSys->addDock(part5, part9, 50, 1);
	dkSys->addDock(part6, part10, 50, 1);
	dkSys->addDock(part7, part11, 50, 1);
	dkSys->addDock(part8, part12, 50, 1);


	Particle* part13 = new Particle({ -10,10,10 });
	addParticle(part13);
	part13->setStartLifeTime(30);
	part13->setImmovible(true);
	Particle* part14 = new Particle({ -3.33,10,10 });
	addParticle(part14);
	part14->setStartLifeTime(30);
	part14->applyGravity();
	Particle* part15 = new Particle({ 3.33,10,10 });
	addParticle(part15);
	part15->setStartLifeTime(30);
	part15->applyGravity();
	Particle* part16 = new Particle({ 10,10, 10 });
	addParticle(part16);
	part16->setStartLifeTime(30);
	part16->setImmovible(true);

	dkSys->addDock(part13, part14, 50, 1);
	dkSys->addDock(part14, part15, 50, 1);
	dkSys->addDock(part15, part16, 50, 1);

	dkSys->addDock(part9, part13, 50, 1);
	dkSys->addDock(part10, part14, 50, 1);
	dkSys->addDock(part11, part15, 50, 1);
	dkSys->addDock(part12, part16, 50, 1);

	addSystem(dkSys);
}
