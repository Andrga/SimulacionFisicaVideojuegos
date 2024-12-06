#pragma once
#include "../RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"

using namespace std;
using namespace physx;

class RBActor
{
public:
	RBActor(PxPhysics* gPhysics) {};
	virtual ~RBActor() = default;

	void update(float t) { cout << pose.p.x << "/" << pose.p.y << "/" << pose.p.z << endl; }

	// visibilidad
	void setVisible(bool vis) {
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
	virtual void setShape(PxShape* shp) {renderItem->shape = shape; }

protected:
	PxTransform pose;
	PxShape* shape;
	RenderItem* renderItem;
};

