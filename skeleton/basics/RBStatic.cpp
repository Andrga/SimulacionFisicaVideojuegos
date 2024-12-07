#include "RBStatic.h"

RBStatic::RBStatic(string nam, Scene* scn, PxPhysics* gPhysics): RBActor(nam, scn, gPhysics)
{

	//pose = PxTransform({ 0,0,0 });
	actor = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	shape = CreateShape(PxBoxGeometry(5,5,5));
	actor->attachShape(*shape);
	//_scene->addActor(*estatico);

	/*actor = gPhysics->createRigidStatic(pose);

	shape = CreateShape(PxBoxGeometry(10, 10, 10));
	actor->attachShape(*shape);*/

	renderItem = new RenderItem(shape, actor, { 1,1,1,1 });
}

RBStatic::~RBStatic()
{
}

void RBStatic::setShape(PxShape* shp)
{
	shape = shp;
	RBActor::setShape(shp);
	actor->attachShape(*shape);
}
