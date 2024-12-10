#pragma once
#include "RBActor.h"

class RBStatic : public RBActor
{
public:
	RBStatic(string nam, Scene* scn, PxPhysics* gPhysics);
	~RBStatic();

	PxRigidActor* getActor() override { return actor; }
	Vector3 getPosition() override { return actor->getGlobalPose().p; };
	void setShape(PxShape* shp, Vector3 siz) override;
	void setPosition(PxVec3 pos) override { GameObject::setPosition(pos); actor->setGlobalPose(*pose); };
	virtual void setVisibility(bool vis) override;

protected:
	PxRigidStatic* actor;

};

