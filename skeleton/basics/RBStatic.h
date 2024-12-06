#pragma once
#include "RBActor.h"

class RBStatic : public RBActor
{
public:
	RBStatic(PxPhysics* gPhysics);
	~RBStatic();

	PxRigidActor* getActor() override { return actor; }
	void setShape(PxShape* shp) override;

private:
	PxRigidStatic* actor;

};

