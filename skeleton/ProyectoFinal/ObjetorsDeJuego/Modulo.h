#pragma once
#include "../../basics/RBDynamic.h"
class Modulo : public RBDynamic
{
public:
	Modulo(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo tipo);
	~Modulo() {};
};
