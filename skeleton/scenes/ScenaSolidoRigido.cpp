#include "ScenaSolidoRigido.h"

ScenaSolidoRigido::ScenaSolidoRigido(Camera* cam, physx::PxPhysics* gPhycs, physx::PxScene* gScn) :Scene(cam, gPhycs, gScn)
{
}

ScenaSolidoRigido::~ScenaSolidoRigido()
{
}

void ScenaSolidoRigido::setup()
{
	RBStatic* suelo = new RBStatic("suelo", this, gPhysics);
	suelo->setShape(CreateShape(PxBoxGeometry(100, 5, 100)));
	gScene->addActor(*suelo->getActor());
	addGameObject(suelo);


	RBDynamic* caja = new RBDynamic("caja", this, gPhysics);
	caja->setPosition({ 0,100,0 });
	caja->setDensity(100);
	gScene->addActor(*caja->getActor());
	addGameObject(caja);

	Particle* particle = new Particle("AMAI", this, { 0,10,0 });
	particle->setImmovible(true);

	addGameObject(particle);

}
