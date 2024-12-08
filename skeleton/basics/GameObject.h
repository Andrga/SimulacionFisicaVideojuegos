#pragma once
#include "Object.h"
#include "../RenderUtils.hpp"
#include <string>
#include <PxPhysicsAPI.h> 

class Scene;

class GameObject : public Object
{
protected:
	// gestion de particulas
	Scene* scene;
	string name;

	// propiedades fisicas de los objetos
	RenderItem* renderItem;
	Vector4 color;
	physx::PxTransform* pose;
	float size = 3;
	float mass = 1;
	Vector3 velocity = { 0,0,0 };

	// propiedades de vida por tiempo de la particula
	float lifeTime = 0;
	float startlifeTime = 10;
public:
	GameObject(string nam, Scene* scn) :name(nam), scene(scn), Object() {};
	virtual ~GameObject() { DeregisterRenderItem(renderItem); };

	virtual bool update(double t) override;

	// cambiar la visibilidad del objeto
	virtual void setVisibility(bool visibility) {
		visibility ?
			RegisterRenderItem(renderItem) :
			DeregisterRenderItem(renderItem);
	};

	//getters
	virtual Vector3 getPosition() { return pose->p; };
	virtual PxQuat getRotation() { return pose->q; };
	float getSize() { return size; };
	string getName() { return name; };
	float getMass() { return mass; };
	Vector3 getVelocity() { return velocity; };

	// setters
	virtual void setPosition(Vector3 pos) { pose->p = pos; };
	virtual void setRotation(PxQuat rot) { pose->q = rot; };
	virtual void setShape(PxShape* shp) { renderItem->shape = shp; };
	void setName(string nam) { name = nam; };
	void setColor(Vector4 col) { renderItem->color = col; color = col; };
	void setSize(float siz) noexcept { size = siz; };
	void setMass(float mas) noexcept { mass = mas; };
	void setVelocity(Vector3 vel) noexcept { velocity = vel; }

	// fuerzas 
	virtual void addForce(float x, float y, float z) {}
	virtual void addForce(Vector3 fc) {}
};

