#include "RBDynamic.h"

RBDynamic::RBDynamic(PxPhysics* gPhysics): RBActor(gPhysics)
{
	pose = PxTransform({ 0,20,0 });
	actor = gPhysics->createRigidDynamic(pose);
	actor->setLinearVelocity({ 0,0,0 });
	actor->setAngularVelocity({ 0,0,0 });
	PxRigidBodyExt::updateMassAndInertia(*actor, 100);
	actor->setMass(100);

	shape = CreateShape(PxBoxGeometry(5, 5, 5));
	actor->attachShape(*shape);
	renderItem = new RenderItem(shape, actor, { 0.8,0.8,0.8,1 });
}

RBDynamic::~RBDynamic()
{
}

void RBDynamic::setShape(PxShape* shp)
{
	shape = shp;
	RBActor::setShape(shp);
	actor->attachShape(*shape);
}
