#include "Modulo.h"

Modulo::Modulo(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo tpo) : RBDynamic("mod" + nam, scn, gPhysics, gScene), tipo(tpo)
{
	switch (tipo)
	{
	case CABINA:
		setShape(CreateShape(PxSphereGeometry(5)), { 5,5,5 });
		setColor({ 0.5,0.5,1,0 });
		break;
	case TANQUE:
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5,5,5 });
		setColor({ 1,1,1,1 });
		break;
	case PROPULSOR:
		setShape(CreateShape(PxSphereGeometry(5)), { 5,5,5 });
		setColor({ 1,0.5,0.5,1 });
		break;
	default:
		break;
	}
}
