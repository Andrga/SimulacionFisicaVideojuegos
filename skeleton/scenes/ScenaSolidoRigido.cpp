#include "ScenaSolidoRigido.h"

ScenaSolidoRigido::ScenaSolidoRigido(physx::PxPhysics* gPhycs, physx::PxScene* gScn) :Scene(gPhycs, gScn)
{
}

ScenaSolidoRigido::~ScenaSolidoRigido()
{
}

void ScenaSolidoRigido::setup()
{
	RBStatic* suelo = new RBStatic(gPhysics);
	suelo->setShape(CreateShape(PxBoxGeometry(100, 5, 100)));
	gScene->addActor(*suelo->getActor());


	RBDynamic* caja = new RBDynamic(gPhysics);
	gScene->addActor(*caja->getActor());
}
