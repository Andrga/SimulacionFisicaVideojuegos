#pragma once
#include "../../basics/RBStatic.h"
#include <functional>

class Button : public RBStatic
{
public: 
	Button(string nam, Scene* scn, PxPhysics* gPhysics);
	~Button();

	void onCollision(GameObject* other) override;
};

