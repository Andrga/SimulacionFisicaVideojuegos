#pragma once
#include "RBActor.h"

class RBDynamic : public RBActor
{
public:
	RBDynamic(string nam, Scene* scn, PxPhysics* gPhysics);
	~RBDynamic();

	bool update(double t) override { return RBActor::update(t); }

	//setters
	void setPosition(PxVec3 pos) override { actor->setGlobalPose(PxTransform(pos)); };
	void setShape(PxShape* shp) override;
	void setDensity(float d) { density = d; };
	// getters
	PxRigidActor* getActor() override { return actor; }

	void setVisibility(bool vis) override;

	void addForce(float x, float y, float z) override { actor->addForce({ x,y,z }); }
	void addForce(Vector3 fc) override { actor->addForce(fc); }

private:
	PxRigidDynamic* actor = nullptr;
	float density = 1.5;
};

