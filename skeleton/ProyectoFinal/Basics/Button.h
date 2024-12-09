#pragma once
#include "../../basics/RBStatic.h"

class Button : public RBStatic
{
private:
	bool pulsado = false;
public:
	Button(string nam, Scene* scn, PxPhysics* gPhysics);
	~Button();

	void onCollision(GameObject* other)override;
	void setVisibility(bool vis) override;
};

