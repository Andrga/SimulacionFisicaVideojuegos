#include "RBDynamic.h"
#include "Scene.h"

RBDynamic::RBDynamic(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene) : RBActor(nam, scn, gPhysics)
{
	density = 0.15f;
	pose = new PxTransform({ 0,20,0 });
	actor = gPhysics->createRigidDynamic(*pose);
	actor->setLinearVelocity({ 0,0,0 });
	actor->setAngularVelocity({ 0,0,0 });
	PxRigidBodyExt::updateMassAndInertia(*actor, density);
	//actor->setMass(100);
	size = { 10,10,10 };
	shape = CreateShape(PxBoxGeometry(size));
	gScene->addActor(*actor);

	shape = CreateShape(PxBoxGeometry(size / 2));
	actor->attachShape(*shape);
	renderItem = new RenderItem(shape, actor, { 0.8,0.8,0.8,1 });

}

RBDynamic::~RBDynamic()
{
}

void RBDynamic::setShape(PxShape* shp, Vector3 siz)
{
	RBActor::setShape(shp, siz);
	actor->attachShape(*shape);
}

void RBDynamic::setVisibility(bool vis)
{
	RBActor::setVisibility(vis);
	scene->pxSceneVisivility(actor, vis);
}
