#include "RBStatic.h"
#include "Scene.h"

RBStatic::RBStatic(string nam, Scene* scn, PxPhysics* gPhysics): RBActor(nam, scn, gPhysics)
{

	pose = new PxTransform({ 0,0,0 });
	actor = gPhysics->createRigidStatic(*pose);
	size = 5;
	shape = CreateShape(PxBoxGeometry(size,size,size));
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

void RBStatic::setShape(PxShape* shp, float siz)
{
	RBActor::setShape(shp, siz);
	actor->attachShape(*shape);
}

void RBStatic::setVisibility(bool vis)
{
	RBActor::setVisibility(vis);
	scene->pxSceneVisivility(actor, vis);
}
