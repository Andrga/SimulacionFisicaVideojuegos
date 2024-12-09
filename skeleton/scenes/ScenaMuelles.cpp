#include "ScenaMuelles.h"

void ScenaMuelles::setup()
{
	// SYSTEMS
	ForceSystem* fsys = new ForceSystem(this);
	addSystem(fsys);

	// --- MUELLES ---	
	// explosion para probar
	expls = new ExplosionGenerator({ -20,50,-10 }, this);
	fsys->addForceGenerator(expls);
	expls->setRadious(30);
	expls->setPotencia(100);

	// suelo muelles
	Particle* sueloM = new Particle("sueloM", this, { -20, 20, 0 });
	addGameObject(sueloM);
	sueloM->setImmovible(true);
	sueloM->setStartLifeTime(50);
	sueloM->setColor({ .5,.5,.5,0 });
	sueloM->setShape(CreateShape(physx::PxBoxGeometry(30, 0.2, 40)), { 30, 0.2, 40 });

	// particula a un ancla
	Particle* part1 = new Particle("part1", this, { -20, 70, 0 });
	addGameObject(part1);
	part1->setStartLifeTime(50);
	part1->applyGravity();
	part1->setColor({ 0.2,0.2,0.8,1 });
	part1->setFloor(20.5);

	// ancla
	Particle* anch = new Particle("anch", this, { -20, 70, 0 });
	addGameObject(anch);
	anch->setImmovible(true);
	anch->setStartLifeTime(50);
	anch->setColor({ 0.2,0.2,0.8,0 });
	anch->setShape(CreateShape(physx::PxBoxGeometry(1, 1, 1)), { 1,1,1 });

	fsys->addForceGenerator(new SpringGenerator(anch->getPosition(), this, 10, 7, part1));

	// cadena de particula
	Particle* part2 = new Particle("part2", this, { -20, 50, 2 });
	addGameObject(part2);
	part2->setStartLifeTime(50);
	part2->applyGravity();
	part2->setColor({ 0.2,0.6,0.8,1 });
	part2->setFloor(20.5);

	fsys->addForceGenerator(new GomaGenerator(this, 10, 7, part2, part1));

	// particula a otra particula
	Particle* part3 = new Particle("part3", this, { -20, 50, 0 });
	addGameObject(part3);
	part3->setStartLifeTime(50);
	part3->applyGravity();
	part3->setMass(2);
	part3->setColor({ 0.8,0.6,0.2,1 });
	part3->setFloor(20.5);

	fsys->addForceGenerator(new GomaGenerator(this, 10, 7, part3, part2));

	Particle* part4 = new Particle("part4", this, { -20, 50, -10 });
	addGameObject(part4);
	part4->setStartLifeTime(50);
	part4->applyGravity();
	part4->setColor({ 0.8,0.2,0.2,1 });
	part4->setFloor(20.5);
	part4->setMass(50);

	fsys->addForceGenerator(new GomaGenerator(this, 10, 7, part4, part3));


	// --- ANCLA K PERSONALIZABLE ---
	// ancla
	Particle* anch2 = new Particle("anch2", this, { -20, 70, -20 });
	addGameObject(anch2);
	anch2->setImmovible(true);
	anch2->setStartLifeTime(50);
	anch2->setColor({ 0.2,0.8,0.2,0 });
	anch2->setShape(CreateShape(physx::PxBoxGeometry(1, 1, 1)), { 1,1,1 });


	// cadena de particula
	Particle* partD = new Particle("partD", this, { -20, 70, -20 });
	addGameObject(partD);
	partD->setStartLifeTime(50);
	partD->applyGravity();
	partD->setColor({ 0.2,0.8,0.2,1 });
	partD->setFloor(20.5);

	sprngGen = new SpringGenerator(anch2->getPosition(), this, 10, 10, partD);
	fsys->addForceGenerator(sprngGen);


	// --- FLOTACION ---
	// generador de fuerza
	fsys->addForceGenerator(new FlotationGenerator(20, this, 1000));


	// particula encima del agua
	Particle* partFlot = new Particle("partFlot", this, { 0, 30, -50 });
	addGameObject(partFlot);
	partFlot->setStartLifeTime(50);
	partFlot->applyGravity();
	partFlot->setSize({ 1,1,1 });
	partFlot->setMass(100);
	partFlot->setColor({ 0.2,0.8,0.2,1 });

	// particula suspendida en el liquido
	Particle* partIntermedio = new Particle("partIntermedio", this, { 10, 20, -50 });
	addGameObject(partIntermedio);
	partIntermedio->setStartLifeTime(50);
	partIntermedio->applyGravity();
	partIntermedio->setSize({ 0.5,0.5,0.5 });
	partIntermedio->setMass(1000);
	partIntermedio->setColor({ 0.8,0.8,0.2,1 });

	// particula hundiendose
	Particle* partHundida = new Particle("partHundida", this, { 20, 30, -50 });
	addGameObject(partHundida);
	partHundida->setStartLifeTime(50);
	partHundida->applyGravity();
	partHundida->setSize({ 1,1,1 });
	partHundida->setMass(10000);
	partHundida->setColor({ 0.8,0.2,0.2,1 });

	// superficie del liquido
	Particle* superficieLiquido = new Particle("superficieLiquido", this, { 10, 20, -50 });
	addGameObject(superficieLiquido);
	superficieLiquido->setImmovible(true);
	superficieLiquido->setStartLifeTime(50);
	superficieLiquido->setColor({ 0.2,0.2,0.8,0 });
	superficieLiquido->setShape(CreateShape(physx::PxBoxGeometry(20, 0.2, 10)), { 20, 0.2, 10 });

	// suelo flotacion
	Particle* sueloF = new Particle("SueloF", this, { 10, 0, -50 });
	addGameObject(sueloF);
	sueloF->setImmovible(true);
	sueloF->setStartLifeTime(50);
	sueloF->setColor({ .5,.5,.5,0 });
	sueloF->setShape(CreateShape(physx::PxBoxGeometry(20, 0.2, 10)), { 20, 0.2, 10 });






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

void ScenaMuelles::keyPressed(unsigned char key, const physx::PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		expls->startGenerate();
		break;
	case 'z':
		sprngGen->setK(1);
		break;
	case 'x':
		sprngGen->setK(10);
		break;
	case 'c':
		sprngGen->setK(100);
		break;
	case 'v':
		sprngGen->setK(1000);
		break;
	default:
		break;
	}
}
