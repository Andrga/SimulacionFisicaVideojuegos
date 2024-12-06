#pragma once
#include "RBActor.h"

class RBStatic : public RBActor
{
public:
	RBStatic(PxPhysics* gPhysics);
	~RBStatic();

	bool update(double t) override { return RBActor::update(t); }

	PxRigidActor* getActor() override { return actor; }
	void setShape(PxShape* shp) override;

private:
	PxRigidStatic* actor;

};
