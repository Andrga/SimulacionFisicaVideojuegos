#include "RBStatic.h"
#include "Scene.h"

RBStatic::RBStatic(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene): RBActor(nam, scn, gPhysics)
{

	pose = new PxTransform({ 0,0,0 });
	actor = gPhysics->createRigidStatic(*pose);
	size = { 5,5,5 };
	shape = CreateShape(PxBoxGeometry(size));
	actor->attachShape(*shape);
	gScene->addActor(*actor);

	renderItem = new RenderItem(shape, actor, { 1,1,1,1 });
}

RBStatic::~RBStatic()
{
}

void RBStatic::setShape(PxShape* shp, Vector3 siz)
{
	RBActor::setShape(shp, siz);
	actor->attachShape(*shape);
}

void RBStatic::setVisibility(bool vis)
{
	RBActor::setVisibility(vis);
	scene->pxSceneVisivility(actor, vis);
}
