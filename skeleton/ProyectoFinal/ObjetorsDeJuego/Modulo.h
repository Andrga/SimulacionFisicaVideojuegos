#pragma once
#include "../../basics/RBDynamic.h"
class Modulo : public RBDynamic
{
protected:
	TipoModulo tipo;
public:
	Modulo(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo tpo);
	~Modulo() {};

	TipoModulo getTipo() { return tipo; };
};
