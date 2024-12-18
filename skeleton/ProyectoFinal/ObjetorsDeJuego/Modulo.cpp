#include "Modulo.h"

Modulo::Modulo(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo tpo, Modulo* cab) : RBDynamic("mod" + nam, scn, gPhysics, gScene), tipo(tpo), cabina(cab)
{
	switch (tipo)
	{
	case CABINA:
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5,5,5 });
		createCabina();
		setColor({ 0,0,1,0 });
		break;
	case TANQUE:
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5,5,5 });
		createTanque();
		setColor({ 1,1,1,0 });
		break;
	case PROPULSOR:
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5,5,5 });
		createPropulsor();
		setColor({ 1,0,0,0 });
		break;
	default:
		break;
	}
	float m = 1000;
	float d = 1.5;
	setDensity(d);
	actor->setLinearDamping(0.99);
	actor->setMass(m);

	float Ih = (m * ((size.x * size.x) + (size.z * size.z)) / 12);
	float Iw = (m * ((size.z * size.z) + (size.y * size.y)) / 12);
	float Id = (m * ((size.x * size.x) + (size.y * size.y)) / 12);

	actor->setMassSpaceInertiaTensor({ Iw, Ih, Id });

	GameObject::setShape(CreateShape(PxSphereGeometry(sizeModule / 2)));
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

void Modulo::createCabina()
{
	renderItemsDecoracion.push_back(new RenderItem(CreateShape(PxBoxGeometry(1, sizeModule / 2, 1)), actor, { 0,0.5,1,1 }));
	renderItemsDecoracion.push_back(new RenderItem(CreateShape(PxSphereGeometry(sizeModule / 3)), actor, { 0,0.5,1,1 }));
	renderItemsDecoracion.push_back(new RenderItem(CreateShape(PxBoxGeometry(sizeModule / 2, 1, 1)), actor, { 0,0.5,1,1 }));
	renderItemsDecoracion.push_back(new RenderItem(CreateShape(PxBoxGeometry(1, 1, sizeModule / 2)), actor, { 0,0.5,1,1 }));
}

void Modulo::createTanque()
{
	renderItemsDecoracion.push_back(new RenderItem(CreateShape(PxBoxGeometry(sizeModule / 2, sizeModule / 2, sizeModule / 2)), actor, { 1,1,1,1 }));
}

void Modulo::createPropulsor()
{
	renderItemsDecoracion.push_back(new RenderItem(CreateShape(PxBoxGeometry(sizeModule / 2, 1, sizeModule / 2)), actor, { 1,0,0,1 }));
	renderItemsDecoracion.push_back(new RenderItem(CreateShape(PxBoxGeometry(1, sizeModule / 2, 1)), actor, { 1,0,0,1 }));
}
