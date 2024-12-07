#pragma once
#include "Object.h"
#include "../RenderUtils.hpp"

class GameObject : public Object
{
protected:
	RenderItem* renderItem;
	float size = 3;
	physx::PxTransform pose;
	Vector4 color;

	// propiedades de vida por tiempo de la particula
	float lifeTime = 0;
	float startlifeTime = 10;
public:
	GameObject() :Object("") {};
	GameObject(string nam) :Object(nam) {};

	// cambiar la visibilidad del objeto
	virtual void setVisibility(bool visibility) {}

	//getters
	virtual PxVec3 getPosition() { return pose.p; }
	virtual PxQuat getRotation() { return pose.q; }
	float getSize() { return size; }

	// setters
	virtual void setPosition(PxVec3 pos) {};
	virtual void setRotation(PxQuat rot) { pose.q = rot; };
	virtual void setShape(PxShape* shp) { renderItem->shape = shp; }
	void setColor(Vector4 col) { renderItem->color = col; color = col; }
	void setSize(float siz) { size = siz; }
};

