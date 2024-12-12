#pragma once
#include "../../basics/RBStatic.h"

class Button : public RBStatic
{
private:
	bool pulsado = false;
public:
	Button(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene);
	~Button();

	void onCollision(GameObject* other)override;
	void setVisibility(bool vis) override;
	void setPulsado(bool puls) { pulsado = puls; };
};

