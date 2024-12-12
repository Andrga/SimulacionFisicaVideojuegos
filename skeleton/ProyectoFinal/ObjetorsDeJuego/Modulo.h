#pragma once
#include "../../basics/RBDynamic.h"
class Modulo : public RBDynamic
{
protected:
	TipoModulo tipo;
	Modulo* cabina;
public:
	Modulo(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo tpo, Modulo* cab);
	~Modulo() {};

	TipoModulo getTipo() { return tipo; };

	bool update(double t) override;
};
