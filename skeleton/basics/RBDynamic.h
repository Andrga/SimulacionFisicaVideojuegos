#pragma once
#include "RBActor.h"

class RBDynamic : public RBActor
{
public:
	RBDynamic(PxPhysics* gPhysics);
	~RBDynamic();

	PxRigidActor* getActor() override { return actor; }
	void setShape(PxShape* shp)override;
private:
	PxRigidDynamic* actor = nullptr;
};

