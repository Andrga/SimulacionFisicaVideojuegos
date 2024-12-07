#include "RBDynamic.h"

RBDynamic::RBDynamic(PxPhysics* gPhysics): RBActor(gPhysics)
{
	density = 10.0f;
	actor = gPhysics->createRigidDynamic(PxTransform({ 0,20,0 }));
	actor->setLinearVelocity({ 0,0,0 });
	actor->setAngularVelocity({ 0,0,0 });
	PxRigidBodyExt::updateMassAndInertia(*actor, density);
	actor->setMass(100);
	//actor->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);

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
