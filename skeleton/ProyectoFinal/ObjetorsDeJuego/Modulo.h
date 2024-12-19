#pragma once
#include "../../basics/RBDynamic.h"
class Modulo : public RBDynamic
{
protected:
	TipoModulo tipo;
	Modulo* cabina;

	vector<RenderItem*> renderItemsDecoracion;

	Vector3 force = { 0,0,0 };
public:
	Modulo(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo tpo, Modulo* cab);
	~Modulo();


	bool update(double t) override;

	void addForce(float x, float y, float z) override { force = { x,y,z }; RBDynamic::addForce(x, y, z); };
	void addForce(Vector3 fc) override { force = fc; RBDynamic::addForce(fc); };

	void createCabina();
	void createTanque();
	void createPropulsor();

	Vector3 getActualForce() { return force; };
	TipoModulo getTipo() { return tipo; };

	void onCollision(GameObject* other) override;
};
