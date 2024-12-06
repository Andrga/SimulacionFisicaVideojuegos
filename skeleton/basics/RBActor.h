#pragma once
#include "../RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"
#include "../basics/Object.h"

using namespace std;
using namespace physx;

class RBActor : public Object
{
public:
	RBActor(PxPhysics* gPhysics) {};
	virtual ~RBActor() = default;

	virtual bool update(double t) override { return true; }

	// visibilidad
	void setVisibility(bool vis) override {
		vis ?
			RegisterRenderItem(renderItem) :
			DeregisterRenderItem(renderItem);
	};

	// getters:
	virtual PxRigidActor* getActor() { return nullptr; };
	PxVec3 getPosition() { return pose.p; };
	PxQuat getRotation() { return pose.q; };

	// setters
	void setPosition(PxVec3 pos) { pose.p = pos; };
	void setRotation(PxQuat rot) { pose.q = rot; };
	virtual void setShape(PxShape* shp) { renderItem->shape = shape; }

protected:
	PxTransform pose;
	PxShape* shape;
	RenderItem* renderItem;
};

