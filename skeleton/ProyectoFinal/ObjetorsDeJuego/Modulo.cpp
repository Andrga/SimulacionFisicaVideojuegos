#include "Modulo.h"

Modulo::Modulo(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo tpo, Modulo* cab) : RBDynamic("mod" + nam, scn, gPhysics, gScene), tipo(tpo), cabina(cab)
{
	switch (tipo)
	{
	case CABINA:
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5,5,5 });
		setColor({ 0.5,0.5,1,0 });
		break;
	case TANQUE:
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5,5,5 });
		setColor({ 1,1,1,1 });
		break;
	case PROPULSOR:
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5,5,5 });
		setColor({ 1,0.5,0.5,1 });
		break;
	default:
		break;
	}
	setDensity(1.5f);
	actor->setLinearDamping(0.9);
	actor->setMass(100);
}

bool Modulo::update(double t)
{

	if (cabina != nullptr)
	{
		// todos los objetos tienen la misma rotacion que la cabina
	}
	/*pose = &(actor->getGlobalPose());
	PxQuat cabRot = pose->q;
	PxVec3 angleY(0, 0, 1);
	pose->q = PxQuat(cabRot.getAngle(), angleY);
	pose->p = { pose->p.x, pose->p.y, 0 };
	actor->setGlobalPose(*pose);*/


	return GameObject::update(t);
}