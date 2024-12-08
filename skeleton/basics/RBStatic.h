#pragma once
#include "RBActor.h"

class RBStatic : public RBActor
{
public:
	RBStatic(string nam, Scene* scn, PxPhysics* gPhysics);
	~RBStatic();

	bool update(double t) override { return RBActor::update(t); }

	PxRigidActor* getActor() override { return actor; }
	void setShape(PxShape* shp) override;
	void setPosition(PxVec3 pos) override { actor->setGlobalPose(PxTransform(pos)); };

	void setVisibility(bool vis) override;

protected:
	PxRigidStatic* actor;

};

