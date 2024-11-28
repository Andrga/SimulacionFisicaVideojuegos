#include "DockScene.h"

void DockScene::setup()
{
	// suelo
	Particle* suelo = new Particle({ -20,0, -20 });
	addParticle(suelo);
	suelo->setImmovible(true);
	suelo->setStartLifeTime(50);
	suelo->setColor({ .5,.5,.5,0 });
	suelo->changeShape(CreateShape(physx::PxBoxGeometry(50, 0.2, 50)));

	// --- MUELLES ---
	DockSystem* dkSys = new DockSystem(this);
	addSystem(dkSys);
	
	// particula a un ancla
	Particle* part1 = new Particle({ -20,50,0 });
	addParticle(part1);
	part1->setStartLifeTime(50);
	part1->setDamping(0.5);
	part1->applyGravity();
	part1->setColor({ 0.2,0.2,0.8,1 });

	// ancla
	Particle* anch = new Particle({ -20,50,0 });
	addParticle(anch);
	anch->setImmovible(true);
	anch->setStartLifeTime(50);
	anch->setColor({ 0.2,0.2,0.8,0 });
	anch->changeShape(CreateShape(physx::PxBoxGeometry(1, 1, 1)));

	dkSys->addDockAnch(anch->getPose().p, part1, 10, 10);

	// cadena de particula
	Particle* part2 = new Particle({ -20,30,0 });
	addParticle(part2);
	part2->setStartLifeTime(50);
	part2->applyGravity();
	part2->setDamping(0.5);
	part2->setMass(2);
	part2->setColor({ 0.2,0.8,0.2,1 });

	dkSys->addDock( part1, part2, 10, 10);

	// particula a otra particula
	Particle* part3 = new Particle({ -20,30,0 });
	addParticle(part3);
	part3->setStartLifeTime(50);
	part3->applyGravity();
	part3->setDamping(0.5);
	part3->setMass(2);
	part3->setColor({ 0.2,0.8,0.2,1 });

	Particle* part4 = new Particle({ -20,30,-10 });
	addParticle(part4);
	part4->setStartLifeTime(50);
	part4->applyGravity();
	part4->setDamping(0.5);
	part4->setColor({ 0.8,0.2,0.2,1 });

	dkSys->addDock(part3, part4, 1, 10);

	// explosion 
	ForceSystem* fsys = new ForceSystem(this);
	addSystem(fsys);

	expls = new ExplosionGenerator({ -20,20,-10 }, this);

	fsys->addForceGenerator(expls);
	expls->setRadious(30);
	expls->setPotencia(200);


	// --- FLOTACION ---
	FloatationSystem* fltSys = new FloatationSystem(this);
	addSystem(fltSys);

	// particula encima del agua
	Particle* partFlot = new Particle({ 0,10, -50 });
	addParticle(partFlot);
	partFlot->setStartLifeTime(50);
	partFlot->applyGravity();
	partFlot->setSize(1);
	partFlot->setColor({ 0.2,0.8,0.2,1 });

	fltSys->addDockFlot(20, partFlot, 1);

	// particula suspendida en el liquido
	Particle* partIntermedio = new Particle({ 10,15, -50 });
	addParticle(partIntermedio);
	partIntermedio->setStartLifeTime(50);
	partIntermedio->applyGravity();
	partIntermedio->setSize(1);
	partIntermedio->setMass(8);
	partIntermedio->setColor({ 0.8,0.8,0.2,1 });

	fltSys->addDockFlot(20, partIntermedio, 1);

	// particula hundiendose
	Particle* partHundida = new Particle({ 20,10, -50 });
	addParticle(partHundida);
	partHundida->setStartLifeTime(50);
	partHundida->applyGravity();
	partHundida->setSize(1);
	partHundida->setMass(100);
	partHundida->setColor({ 0.8,0.2,0.2,1 });

	fltSys->addDockFlot(20, partHundida, 1);

	// superficie del liquido
	Particle* superficieLiquido = new Particle({ 10,20, -50 });
	addParticle(superficieLiquido);
	superficieLiquido->setImmovible(true);
	superficieLiquido->setStartLifeTime(50);
	superficieLiquido->setColor({ 0,0,1,0 });
	superficieLiquido->changeShape(CreateShape(physx::PxBoxGeometry(20, 0.2, 10)));

	





	// tela ?
	/*
		 1--2--3--4
		 |  |  |  |
		 5--6--7--8
		 |  |  |  |
		 9-10-11-12
		 |  |  |  |
		13-14-15-16
	*/
	/*
	Particle* part1 = new Particle({ -10,10,-10 });
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
	Particle* part4 = new Particle({ 10,10,-10 });
	addParticle(part4);
	part4->setStartLifeTime(30);
	part4->setImmovible(true);

	dkSys->addDock(part1, part2, 100, 4);
	dkSys->addDock(part2, part3, 100, 4);
	dkSys->addDock(part3, part4, 100, 4);


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

	dkSys->addDock(part5, part6, 100, 4);
	dkSys->addDock(part6, part7, 100, 4);
	dkSys->addDock(part7, part8, 100, 4);

	dkSys->addDock(part1, part5, 100, 4);
	dkSys->addDock(part2, part6, 100, 4);
	dkSys->addDock(part3, part7, 100, 4);
	dkSys->addDock(part4, part8, 100, 4);

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

	dkSys->addDock(part9, part10, 100, 4);
	dkSys->addDock(part10, part11, 100, 4);
	dkSys->addDock(part11, part12, 100, 4);

	dkSys->addDock(part5, part9, 100, 4);
	dkSys->addDock(part6, part10, 100, 4);
	dkSys->addDock(part7, part11, 100, 4);
	dkSys->addDock(part8, part12, 100, 4);


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

	dkSys->addDock(part13, part14, 100, 4);
	dkSys->addDock(part14, part15, 100, 4);
	dkSys->addDock(part15, part16, 100, 4);

	dkSys->addDock(part9, part13, 100, 4);
	dkSys->addDock(part10, part14, 100, 4);
	dkSys->addDock(part11, part15, 100, 4);
	dkSys->addDock(part12, part16, 100, 4);

	addSystem(dkSys);*/
}

void DockScene::keyPressed(unsigned char key, const physx::PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		expls->startGenerate();
	default:
		break;
	}
}
