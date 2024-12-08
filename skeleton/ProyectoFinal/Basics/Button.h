#pragma once
#include "../../basics/RBStatic.h"
class Button : public RBStatic
{
public: 
	Button(string nam, Scene* scn, PxPhysics* gPhysics);
	~Button();
};

