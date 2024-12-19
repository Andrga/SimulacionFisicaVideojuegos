#include "Modulo.h"
#include "../Scenes/ScenaLaunch.h"

Modulo::Modulo(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo tpo, Modulo* cab) : RBDynamic("mod" + nam, scn, gPhysics, gScene), tipo(tpo), cabina(cab)
{
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5,5,5 });
	switch (tipo)
	{
	case CABINA:
		cabina = this;
		createCabina();
		setColor({ 0,0,1,0 });
		break;
	case TANQUE:
		createTanque();
		setColor({ 1,1,1,0 });
		break;
	case PROPULSOR:
		createPropulsor();
		setColor({ 1,0,0,0 });
		break;
	default:
		break;
	}
	float m = 1000;
	float d = 1.5;
	setDensity(d);
	actor->setLinearDamping(0.8);
	actor->setMass(m);

	// formulas cuboide puesto que los modulos son tratados como cubos a pesar de que se vean con otras geometrias
	float Ih = (m * ((size.x * size.x) + (size.z * size.z)) / 12);
	float Iw = (m * ((size.z * size.z) + (size.y * size.y)) / 12);
	float Id = (m * ((size.x * size.x) + (size.y * size.y)) / 12);

	actor->setMassSpaceInertiaTensor({ Iw, Ih, Id });
	// se ensenia el collider en forma de circulo pero en realidad se aplica como un cubo
	GameObject::setShape(CreateShape(PxSphereGeometry(sizeModule / 2)));
}

Modulo::~Modulo()
{
	for (auto ri : renderItemsDecoracion)
		DeregisterRenderItem(ri);
}

bool Modulo::update(double t)
{
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

void Modulo::onCollision(GameObject* other)
{
	string name = other->getName();
	if (name.substr(0, 3) == "plt") {
		if (cabina->getVelocity().x >= EXPLOSION_VELOCITY.x || cabina->getVelocity().y >= EXPLOSION_VELOCITY.y || cabina->getVelocity().z >= EXPLOSION_VELOCITY.z) {
			((ScenaLaunch*)scene)->exploteSpaceship();
		}

	}
	else if (name.substr(0, 6) == "radPlt") {
		((ScenaLaunch*)scene)->setPlaneta(name.substr(6, name.length() - 1));
	}

}