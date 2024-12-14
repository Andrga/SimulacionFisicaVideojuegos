#include "ScenaSolidoRigido.h"

ScenaSolidoRigido::ScenaSolidoRigido(SceneManager* scnMang, physx::PxPhysics* gPhycs, physx::PxScene* gScn) :Scene(scnMang, gPhycs, gScn)
{
}

ScenaSolidoRigido::~ScenaSolidoRigido()
{
}

void ScenaSolidoRigido::setup()
{
	
	RBStatic* suelo = new RBStatic("suelo", this, gPhysics, gScene);
	suelo->setShape(CreateShape(PxBoxGeometry(100, 100, 100)), { 100, 100, 100 });
	suelo->setPosition({ 0,-200,0 });

	addGameObject(suelo);


	RBDynamic* caja = new RBDynamic("caja", this, gPhysics, gScene);
	caja->setPosition({ 0,0,0 });
	caja->setDensity(1);
	addGameObject(caja);

	RBDynamic* caja2 = new RBDynamic("caja2", this, gPhysics, gScene);
	caja2->setPosition({ 0,20,0 });
	caja2->setDensity(100);
	addGameObject(caja2);

	Particle* particle = new Particle("AMAI", this, { 110,20,0 });
	particle->setImmovible(false);
	particle->applyGravity();
	particle->setFloor(-300.0f);

	addGameObject(particle);

	/*Particle* particle2 = new Particle("AMAI2", this, { 0,0,0 });
	particle2->setImmovible(true);

	addGameObject(particle2);*/

}

void ScenaSolidoRigido::show()
{
	
	Scene::show();
	display_text1 = "SOLIDO RIGIDO";
	camera->moveTo({ 0,0,100 });
	camera->setMovible(true);
}
