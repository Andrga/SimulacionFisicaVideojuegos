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
	RBActor(string nam, Scene* scn, PxPhysics* gPhysics) : GameObject(nam, scn) { setStartLifeTime(-1); };
	virtual ~RBActor() = default;

	// visibilidad
	virtual void setVisibility(bool vis) override { GameObject::setVisibility(vis); };

	// getters:
	virtual PxRigidActor* getActor() { return nullptr; };
	
};

