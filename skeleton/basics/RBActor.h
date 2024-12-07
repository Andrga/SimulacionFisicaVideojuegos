#pragma once
#include "../RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"
#include "GameObject.h"

using namespace std;
using namespace physx;

class RBActor : public GameObject
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


protected:
	//PxTransform* pose;
	PxShape* shape;
};

