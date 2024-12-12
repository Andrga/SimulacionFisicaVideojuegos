#pragma once
#include "RBActor.h"

class RBDynamic : public RBActor
{
public:
	RBDynamic(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene);
	~RBDynamic();

	//setters
	void setPosition(PxVec3 pos) override { GameObject::setPosition(pos); actor->setGlobalPose(*pose); };
	void setShape(PxShape* shp, Vector3 siz) override;
	void setDensity(float d) { density = d; };
	void setVisibility(bool vis) override;
	// getters
	PxRigidActor* getActor() override { return actor; };
	Vector3 getPosition() override { return actor->getGlobalPose().p; };

	void addForce(float x, float y, float z) override { actor->addForce({ x,y,z }); }
	void addForce(Vector3 fc) override { actor->addForce(fc); }

protected:
	PxRigidDynamic* actor = nullptr;
	float density = 1.5;
};

